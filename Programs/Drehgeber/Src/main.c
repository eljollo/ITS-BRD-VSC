/**
 * @file main.c
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief umfasst die Ermittlung von Messwerten mittels Drehgeber samt
 * Darstellung von Winkel und Winkelgeschwindigkeit auf dem Display.
 */

// ============ INLCUDES ============
#include "LCD_GUI.h"
#include "calculations.h"
#include "i_o_module.h"
#include "init.h"
#include "phase.h"
#include "timer.h"
#include "timer_hm.h"
#include <stdbool.h>
#include <stdint.h>

// ============ Konstanten ============
static const uint64_t TICKS_300_MS = 27000000ULL;
static const uint64_t TICKS_3_S = 270000000ULL;

#define OSZI

typedef struct {
   PhaseCountSnapshot starter;
   uint64_t start_ticks;
} CalcWindow;

int main(void) {
   // Initialisierung
   initITSboard();
   initTimer();
   GUI_init(DEFAULT_BRIGHTNESS);
   init_display_output();
   timer_reset_extension();
   phase_reset();

   CalcOutput calc_output;

   IoInputs input;

   read_all_inputs(&input);

   CalcWindow window = {.starter = {0}, .start_ticks = input.timer_ticks};

   // ###################################################
   // ################# START SUPERLOOP #################
   // ###################################################
   while (true) {
#ifdef OSZI
      set_pin_for_oszilloskop();
#endif

      read_all_inputs(&input);

      // falls S6 gedrückt
      if (input.reset_pressed) {
         phase_reset();
         reset_display();
         reset_all_leds();

         window.starter = (PhaseCountSnapshot){0};
         window.start_ticks = input.timer_ticks;

         continue; // neuer Superloop Durchlauf
      }

      // alles tutti und Input wird in phase_state überführt
      phase_process(input.phase_bits, input.timer_ticks);

      if (phase_has_error()) {
         set_gpioe_error(true);
         continue;
      }

      // speichert phasen-infos/stats der aktuellen phase
      PhaseCountSnapshot latest = phase_get_counter_sample();

      // nimmt drehrichtung entgegen
      Direction direction = phase_get_last_direction();

      // verstrichene Zeit = aktueller tick wert minus ticks der letzten
      uint64_t elapsed = input.timer_ticks - window.start_ticks;

      // check auf Phasenwechsel stattgefunden
      bool phase_changed = latest.total_changes != window.starter.total_changes;

      // check ob seit verstrichener Zeit > 300ms eine phase gewechselt hat
      if (elapsed >= TICKS_300_MS) {
         if (phase_changed) {
            // Berechnung
            calc_output.angle = calculate_angle(latest.phase_counter);
            calc_output.speed = calculate_speed(window.starter, latest);

            // aktueller durchlauf wird startpunkt von neuem zeitfenster
            window.starter = latest;
            window.start_ticks = input.timer_ticks;

         } else if (elapsed >= TICKS_3_S) { // wenn 3s nichts passiert
            calc_output.angle = calculate_angle(latest.phase_counter);
            calc_output.speed = calculate_speed(window.starter, latest);

            // Zeitpunkt für startzeitfenster wird aktualisiert
            window.start_ticks = input.timer_ticks;
         }
      }

      set_all_output(direction, phase_has_error(), latest.phase_counter);
      display_update(calc_output.angle, calc_output.speed);

      // #ifdef OSZI
      //       reset_pin_for_oszilloskop();
      // #endif
   }
}

// EOF
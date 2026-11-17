/**
 * @file main.c
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief umfasst die Ermittlung von Messwerten mittels Drehgeber samt
 * Darstellung von Winkel und Winkelgeschwindigkeit auf dem Display.
 */

/* Includes ------------------------------------------------------------------*/

// #include "main.h"
#include "LCD_GUI.h"
// #include "LCD_Touch.h"
#include "calculations.h"
#include "i_o_module.h"
#include "init.h"
// #include "lcd.h"
// #include "stm32f4xx.h"
// #include "stm32f4xx_hal.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// #include "inputoutput.h"
#include "phase.h"
#include "timer_hm.h"

static const uint64_t TICKS_300_MS = 27000000ULL;
static const uint64_t TICKS_3_S = 270000000ULL;

int main(void) {

   initITSboard(); // Initialisierung des ITS Boards
   GUI_init(DEFAULT_BRIGHTNESS);

   init_display_output(); // Display initialisueren

   timer_reset_extension();

   phase_reset();

   IoInputs input;
   // setzt relevante phasenwerte auf 0 / false
   PhaseCountSnapshot calc_starting_point = {0};

   bool has_calc_starting_point = false;

   // letzte ticks des zeitfensters für berechnung
   uint64_t last_calculation_ticks = 0;
   // wird mMn nicht benötigt, da in PhaseCountSnapshot change_ticks existiert
   // oder ist dies nochmal losgelöst für die berechnung?
   // Sollte dann aber dennoch in PhaseCountSnapshot angelegt sein
   // oder ich müsste es in PhaseCalcSnapshot übersetzen oder so
   // --> checken wie häufig was wo bereits existiert

   // gibt es schon eine startzeit
   bool has_initial_time = false;

   // zähler für phasenwechsel
   uint64_t last_displayed_change_number = 0; // zähler für phasenwechsel

   // START SUPERLOOP
   // ####################################################
   // ####################################################
   // ####################################################
   while (true) {

      read_all_inputs(&input);

      uint64_t now_ticks = timer_extend(input.raw_timer_ticks);

      // setze eingelesene bits & timestamp in struct von phase.c
      Phase current = {
          .phase_bits = input.phase_bits,
          .timer_ticks = now_ticks,
      };

      // check ob es bereits ein start des 300ms Zeitfensters gibt (ansonsten
      // wird aktueller tick gesetzt)
      if (!has_initial_time) {
         last_calculation_ticks = now_ticks;
         has_initial_time = true;
      }

      // falls S6 gedrückt
      if (input.reset_pressed) {
         phase_reset(); // aus phase.c

         init_display_output();

         reset_all_leds();

         timer_reset_extension();

         has_calc_starting_point = false;
         // resets PhaseCounterSnapshot informationen
         calc_starting_point = (PhaseCountSnapshot){0};
         last_displayed_change_number = 0;
         last_calculation_ticks = now_ticks;

         continue; // neuer Superloop Durchlauf
      }

      // alles tutti und die aktuelle Phase wird prozessiert => mit eingelesenen
      // Werten arbeiten
      phase_process(current);

      if (phase_has_error()) {

         set_gpioe_error(true);

         continue;
      }

      // speichert phasen-infos/stats der aktuellen phase
      PhaseCountSnapshot latest = phase_get_counter_sample();

      // nimmt drehrichtung entgegen
      Direction direction = phase_get_last_direction();

      // wenn es noch keinen starzeitpunkt für berechnung gab und ein legiter
      // phasenwechsel stattgefunden hat wird startpunkt für zeitfenster gesetzt
      // und der check ob startpunkt vorhanden auf true gesetzt
      if (!has_calc_starting_point && latest.has_last_change) {
         calc_starting_point = latest;
         has_calc_starting_point = true;
      }

      // verstrichene Zeit = aktueller tick wert minus ticks der letzten
      // berechnung (im 1. durchgang die aktuellen ticks )
      uint64_t elapsed = now_ticks - last_calculation_ticks;

      // check ob seit verstrichener Zeit > 300ms eine phase gewechselt hat
      if (elapsed >= TICKS_300_MS) {
         bool change_since_last_display =
             latest.change_number != last_displayed_change_number;

         if (change_since_last_display) {
            // Winkelberechnung
            double angle = calculate_angle(latest.count);

            double speed = 0.0;
            bool speed_valid = false;

            // wenn calc_starting_point besteht und phase sich verändert hat
            // berechnung der Geschwindigkeit
            if (has_calc_starting_point &&
                (latest.change_number > calc_starting_point.change_number)) {
               speed_valid =
                   calculate_speed(calc_starting_point, latest, &speed);
            }

            // WICHTIG!!! MODUL: DISPLAY – neue Darstellung nur vormerken.
            // Nach nur EINEM Wechsel gibt es noch keine zwei Wechselzeitpunkte:
            // Geschwindigkeit zunächst "--".
            // display_queue_values(angle, speed_valid, speed);

            snprintf(angle_buff, sizeof(angle_buff), "%8.1f", angle);
            snprintf(speed_buff, sizeof(speed_buff), "%8.1f", speed);
            // ggf beide snprintf in funktion fill_buffer oder so überführen

            // aktueller durchlauf nach berechnung wird startpunkt von neuem
            // zeitfenster
            calc_starting_point = latest;
            has_calc_starting_point = latest.has_last_change;
            last_displayed_change_number = latest.change_number;
            last_calculation_ticks = now_ticks;

         } else if (elapsed >= TICKS_3_S) { // wenn 3s nichts passiert
            double angle = calculate_angle(latest.count);

            // "leere" geschwindigkeit ausgegeben
            snprintf(angle_buff, sizeof(angle_buff), "%8.1f", angle);

            last_calculation_ticks =
                now_ticks; // Zeitpunkt für startzeitfenster wird aktualisiert
         }
      }

      // HIER LED AUSGABE EINFÜGEN ZU:
      // - RICHTUNG (D23 (vorwärts), D22 (rückwärts))
      // - ANZAHL PHASENWECHSEL (D8 - D15)
      set_all_output(direction, phase_has_error(), latest.change_number);

      // MODUL: display – höchstens ein vorbereitetes Zeichen
      // tatsächlich über das I/O-Modul ausgeben.
      display_update();
   }
}

// EOF
/**
 * @file main.c
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief umfasst die Ermittlung von Messwerten mittels Drehgeber samt Darstellung von Winkel und Winkelgeschwindigkeit auf dem Display.
 */

/* Includes ------------------------------------------------------------------*/

#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "../Inc/init.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"

#include <stdbool.h>
#include <stdint.h>

#include "../Inc/calculations.h"
#include "../Inc/structs.h"
#include "../Inc/phase.h"
#include "../Inc/inputoutput.h"
#include "timer.h"

static const uint64_t TICKS_300_MS = 27000000ULL;
static const uint64_t TICKS_3_S = 270000000ULL;

int main(void) {
   initITSboard(); // Initialisierung des ITS Boards

   // GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
   // TP_Init(false); // Initialisierung des LCD Boards mit Touch

   // // Begruessungstext
   // lcdPrintlnS("Hallo liebes TI-Labor (c-project)");

   // Test in Endlosschleife
   // const int POLL_DELAY = 10000;
   // while (1) {
   //    HAL_Delay(POLL_DELAY);
   // }

   // =============================================================================
   // =============================================================================
   // =============================================================================

   // über I/O: S6 & Phase mit Zeitstempel lesen (I/O)
   // aktuelle & vorherige Phase ermitteln -> Phasenwechsel und -zähler (Phase)
   // Winkel und Winkelgeschwindigkeit berechnen (calculations)
   // LEDs aktualisieren (I/O)
   // Display aktualisieren alle 300ms (Display).

   // // WICHTIG!!! I/O MODUL
   // io_init();

   // MODUL: timer – Erweiterung des 32-Bit-Zeitstempels initialisieren.
   timer_reset();

   // // MODUL: phase – Zähler, Richtung und Fehler initialisieren.
   phase_reset();

   // // MODUL: display – LCD-Layout einmalig schreiben.
   // display_init();


   // HIER GGF NOCH WEITERE VARIABLEN FÜR DIE BERECHNUNG ANLEGEN ODER ABER STRUCT FÜR BERECHNUNG
   // also: 
   // - startwerte für Berechnung (Berechnungszeitfenster)
   // --> gibt es bereits einen Zeitfensterstart ? (bool)
   // --> Timestamp / ticks / letzter Zeitstempel für Berechnung
   // --> Zählerstand (aus phase struct ?)
   PhaseCountSnapshot calc_starting_point = {0};   // setzt relevante phasenwerte auf 0 / false
   bool has_calc_starting_point = false;           // checkt obs schon nen startpunkt für Rechnungen gibt

   uint64_t last_calculation_ticks = 0;            // letzte ticks des zeitfensters für berechnung
   bool has_initial_time = false;                  // gibt es schon eine startzeit / ersten getrackten wechsel

   uint64_t last_displayed_change_number = 0;      // zähler für phasenwechsel unabhängig von richtung


   // START SUPERLOOP

   for (;;) {

      // WICHTIG!!! I/O MODUL
      // Phase, Timer-Rohwert und S6 am Anfang der Schleife erfassen
      // Einlesen Phase (+ timestamp) und S6 (Reset-Button)
      IoInputs input = read_input();

      // MODUL: timer ticks (rohwerte) in fortlaufende Zeit umwandeln
      uint64_t now_ticks = timer_extend(input.raw_timer_ticks);

      // setze eingelesene bits & timestamp in struct von phase.c
      Phase current = {                         
            .phase_bits = input.phase_bits,
            .timer_ticks = now_ticks,
      };
      
      // check ob es bereits ein start des 300ms Zeitfensters gibt (ansonsten wird aktueller tick gesetzt)
      if(!has_initial_time){
         last_calculation_ticks = now_ticks;
         has_initial_time = true;
      }

   
      // falls S6 gedrückt
      if (input.reset_pressed) {
         phase_reset(); // aus phase.c reset 

         // WICHTIG!!! DISPLAY MODUL: display – ausstehende alte Wertausgabe verwerfen.
         initial_display_output();

         // WICHTIG!!! I/O MODUL
         led_reset();
         timer_reset();

         has_calc_starting_point = false;
         calc_starting_point  = (PhaseCountSnapshot){0} ; // resets PhaseCounterSnapshot informationen
         last_displayed_change_number = 0;
         last_calculation_ticks = now_ticks;

         continue; // neuer Superloop Durchlauf
      }

      // alles tutti und die aktuelle Phase wird prozessiert => mit eingelesenen Werten arbeiten
      phase_process(current);

      if(phase_has_error()){
         // WICHTIG!!! I/O MODUL
         show_error();
         
         continue;
      }

      PhaseCountSnapshot latest = phase_get_counter_sample(); // speichert phasen-infos/stats der aktuellen phase

      Direction direction = phase_get_last_direction(); // nimmt drehrichtung entgegen

      // HIER LED AUSGABE EINFÜGEN ZU:
      // - RICHTUNG (D23 (vorwärts), D22 (rückwärts))
      // - ANZAHL PHASENWECHSEL (D8 - D15)

      // WICHTIG!!! I/O MODUL
      // Umwandlung nach uint8_t liefert die niederwertigsten acht bit
      write_phase_number_to_led((uint8_t)latest.count);
      // WICHTIG!!! I/O MODUL
      write_phase_number_to_led(direction);

      // wenn es noch keinen starzeitpunkt für berechnung gab und ein legiter phasenwechsel stattgefunden hat 
      // wird startpunkt für zeitfenster gesetzt und der check ob startpunkt vorhanden auf true gesetzt
      if (!has_calc_starting_point && latest.has_last_change) {
         calc_starting_point = latest;
         has_calc_starting_point = true;
      }

      uint64_t elapsed = now_ticks - last_calculation_ticks; // verstrichene Zeit = aktueller tick wert minus ticks der letzten berechnung (im 1. durchgang die aktuellen ticks )

      if (elapsed >= TICKS_300_MS) {
         bool change_since_last_display = latest.change_number != last_displayed_change_number; // check ob seit verstrichener Zeit > 300ms eine phase gewechselt hat

         if (change_since_last_display) {
            // Winkelberechnung
            double angle = calculate_angle(latest.count);
            
            double speed = 0.0;
            bool speed_valid = false;

            if (has_calc_starting_point && (latest.change_number > calc_starting_point.change_number)) { // wenn calc_starting_point besteht und phase sich verändert hat
               // berechnung der Geschwindigkeit
               speed_valid = calculate_speed(calc_starting_point, latest, &speed);
            }

            // WICHTIG!!! MODUL: DISPLAY – neue Darstellung nur vormerken.
            // Nach nur EINEM Wechsel gibt es noch keine zwei Wechselzeitpunkte: Geschwindigkeit zunächst "--".
            //display_queue_values(angle, speed_valid, speed);

            // aktueller durchlauf nach berechnung wird startpunkt von neuem zeitfenster
            calc_starting_point = latest;
            has_calc_starting_point = latest.has_last_change;
            last_displayed_change_number = latest.change_number;
            last_calculation_ticks = now_ticks;

            } else if (elapsed >= TICKS_3_S) { // wenn 3s nichts passiert
               double angle = calculate_angle(latest.count);
               // MODUL: display
               //display_queue_values(angle, true, 0.0); // neben winkel wird "leere" geschwindigkeit ausgegeben

               last_calculation_ticks = now_ticks; // Zeitpunkt für startzeitfenster wird aktualisiert
            }
         }
      // MODUL: display – höchstens ein vorbereitetes Zeichen
      // tatsächlich über das I/O-Modul ausgeben.
      //display_step();
   }
}

// EOF
/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "init.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"

int main(void) {
   initITSboard(); // Initialisierung des ITS Boards

   GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
   TP_Init(false); // Initialisierung des LCD Boards mit Touch

   // Begruessungstext
   lcdPrintlnS("Hallo liebes TI-Labor (c-project)");

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

   
   // START SUPERLOOP

   // // Einlesen Phase (+ timestamp) und S6 (Reset-Button)
   // Phase current = io_read_phase_sample(); // get pin A and B & timestamp und setze sie in 
   // bool reset_pressed = io_read_s6();

   // // mit eingelesenen Werten arbeiten
   // phase_process(current);    // phase current verarbeiten   
   
   // calculation-Funktion ausführen

   // LED-Output (Fehler, Richtung, Zähler Phasenwechsel) -> Alles aus state
   // Display-Output


}

// EOF

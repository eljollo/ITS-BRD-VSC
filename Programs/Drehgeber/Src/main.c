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

   // get pin A and B

   // phase current


   // phase current zu phase previous

}

// EOF

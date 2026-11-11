/**
 ******************************************************************************
 * @file    main.c
 * @author  Lasse 
 * @brief   hier fürs testen von inputoutput-Funktionen
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "init.h"
#include "lcd.h"
#include "LCD_general.h"
#include "timer.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "../Inc/inputoutput.h"

//void initial_display_output(void); // forward declaration for the display init routine

int main(void) {
   initITSboard(); // Initialisierung des ITS Boards

   GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
   TP_Init(false); // Initialisierung des LCD Boards mit Touch

   // Begruessungstext
   initial_display_output();

   // Test in Endlosschleife
   const int POLL_DELAY = 10000;
   while (1) {
      HAL_Delay(POLL_DELAY);
   }
}

// EOF

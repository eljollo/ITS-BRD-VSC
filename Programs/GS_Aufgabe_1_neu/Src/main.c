/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

// #include "LCD_GUI.h"
// #include "LCD_Touch.h"
#include "error_handling.h"
#include "init.h"
// #include "lcd.h"
#include "scanner.h"
// #include "stm32f4xx_hal.h"
#include "display.h"
#include "stack.h"
#include "token.h"
// #include ""


// error funktion
static void print_error(enum Status status) {
   set_err_mode();  
   switch (status) {
      case DIV_BY_ZERO:
      print_stdout("Division durch Null");
      break;
      case ARITH_OVERFLOW:
      print_stdout("Bereichsueberschreitung");
      break;
      case STACK_OVERFLOW:
      print_stdout("Stack Overflow");
      break;
      case STACK_UNDERFLOW:
      print_stdout("Stack Underflow");
      break;
      case EMPTY_STACK:
      print_stdout("Stack ist leer");
      break;
      case SUCCESS:
      break;
   }
}


int main(void) {
   initITSboard(); // Initialisierung des ITS Boards

   // TASCHENRECHNER
   init_display();
   init_stack();

   while (1) {
      enum Status status = SUCCESS;
      T_token eingabe = next_token();

      switch (eingabe.tok) {
         // stack functions
         case PRT: {      
            int val;
            status = funct_p(&val);
            if (status != SUCCESS) {
               print_error(status);
            }
         break;
         }
         case PRT_ALL: {
            int intarray[3];
            int counter;
            status = funct_pthree(intarray, &counter);
            if (status != SUCCESS) {
               print_error(status);
            }
         break;
         }
         case DOUBLE: {
            status = funct_d();
            if (status != SUCCESS) {
               print_error(status);
            }
         break;
         }
         case SWAP: {
            status = funct_r();
            if (status != SUCCESS) {
               print_error(status);
            }
         break;            
         }
         // arithmetic functions
         case PLUS: {}
         case MINUS: {}
         case MULT: {}
         case DIV: {}
         case CLEAR: {}
      }
   }
}

// EOF
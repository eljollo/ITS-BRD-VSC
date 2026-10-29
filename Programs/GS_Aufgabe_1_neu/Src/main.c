/**
 ******************************************************************************
 * @file    main.c
 * @author  Lasse Bruhn, Matr.Num.: 2880211, Thomas Ramba, Matr.Num.: 284259
 * @brief   contains the implementation of the main function
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

// #include "LCD_GUI.h"
// #include "LCD_Touch.h"
#include "main.h"
#include "error_handling.h"
#include "init.h"
// #include "lcd.h"
#include "scanner.h"
// #include "stm32f4xx_hal.h"
#include "arithmetics.h"
#include "display.h"
#include "stack.h"
#include "token.h"
#include "output.h"
#include <stdbool.h>
#include <stdio.h>
// #include ""


int main(void) {
   initITSboard(); // Initialisierung des ITS Boards

   // TASCHENRECHNER
   init_display();
   init_stack();
   bool fehlermodus = false;

   while (1) {
      enum Status status = SUCCESS;
      T_token eingabe = next_token();

      if (fehlermodus && eingabe.tok != CLEAR) {
         continue;
      }

      switch (eingabe.tok) {
      // stack functions
      case NUMBER: {
         status = push(eingabe.val);
         break;
      }
      case PRT: {
         status = funct_p();
         break;
      }
      case PRT_ALL: { // in funktion umziehen-> push & pop nutzen 
         status = funct_pthree();
         break;
      }
      case DOUBLE: {
         status = funct_d();
         break;
      }
      case SWAP: {
         status = funct_r();
         break;
      }
      // arithmetic functions
      case PLUS: {
         status = add();
         break;
      }
      case MINUS: {
         status = subtract();
         break;
      }
      case MULT: {
         status = multiply();
         break;
      }
      case DIV: {
         status = divide();
         break;
      }
      case CLEAR: {
         init_stack();
         set_normal_mode();
         fehlermodus = false;
         break;
      }
      default: {
         set_err_mode();
         print_stdout("Ungueltige Eingabe");
         fehlermodus = true;
         break;
      }
      }

      if (status != SUCCESS ) {
         fehlermodus = true;
         print_error(status);
      }
   }
}

// EOF
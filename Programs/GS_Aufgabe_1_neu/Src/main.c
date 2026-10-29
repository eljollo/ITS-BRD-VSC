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
#include "display.h"
#include "stack.h"
#include "token.h"
#include <stdbool.h>
#include <stdio.h>
#include "arithmetics.h"
// #include ""

// Konstanten
#define TEXT_LENGTH 20

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
            int val;
            status = funct_p(&val);
            if (status == SUCCESS) {
               clear_stdout();
               char ausgabe[TEXT_LENGTH];
               sprintf(ausgabe, "%d\n", val);
               print_stdout(ausgabe);
            }
            if (status == EMPTY_STACK) {
               clear_stdout();
               char ausgabe[TEXT_LENGTH];
               sprintf(ausgabe, "Stack ist leer");
               print_stdout(ausgabe);
            }
            break;
         }
         case PRT_ALL: {
            int intarray[3];
            int counter;
            status = funct_pthree(&counter, intarray);
            if (status == SUCCESS) {
               clear_stdout();
               for (int i = 0; i < counter; i++) {
                  char ausgabe[TEXT_LENGTH];
                 sprintf(ausgabe, "%d\n", intarray[i]);
                  print_stdout(ausgabe);
               }
            }
            if (status == EMPTY_STACK) {
               clear_stdout();
               char ausgabe[TEXT_LENGTH];
               sprintf(ausgabe, "Stack ist leer");
               print_stdout(ausgabe);
            }
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

      if (status != SUCCESS && status != EMPTY_STACK) {
         fehlermodus = true;
         print_error(status);
      }

   }
}

// EOF
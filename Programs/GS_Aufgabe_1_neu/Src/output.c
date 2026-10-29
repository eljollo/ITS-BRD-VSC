#include "error_handling.h"
#include "stack.h"
#include "display.h"
#include <stdio.h>

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


enum Status funct_p(void) {
    int operand1 = 0;

    enum Status status = pop(&operand1); // pops value to the address of operand1
    if (status != SUCCESS) {
       return EMPTY_STACK;
    }
    clear_stdout();
    char ausgabe[TEXT_LENGTH];
    sprintf(ausgabe, "%d\n", operand1);
    print_stdout(ausgabe);
    return SUCCESS;
}

// Funktion P (druckt die drei obersten Werte des Stacks aus)
enum Status funct_pthree(void) {
    int intarray[3];
    int counter = 0;
    enum Status status = pop(&intarray[0]); // pops value to the address of operand1
    if (status != SUCCESS) {
        return EMPTY_STACK;
    }
    for (counter = 1 ; counter < 3 && status == SUCCESS ; counter++) {
        status = pop(&intarray[counter]);
    }
    clear_stdout();
    while (counter>=0) {
        char ausgabe[TEXT_LENGTH];
        sprintf(ausgabe, "%d\n", intarray[counter]);
        print_stdout(ausgabe);
        push(intarray[counter]);
        counter--;
    }
    return SUCCESS;

}



#include "error_handling.h"
#include "stack.h"
#include "display.h"
#include <stdio.h>

// Konstanten
#define TEXT_LENGTH 20

// error funktion
void print_error(enum Status status) {
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
    push(operand1);
    return SUCCESS;
}

// Funktion P (druckt die drei obersten Werte des Stacks aus)
enum Status funct_pthree(void) {
    int intarray[3];
    int counter = 0;
    enum Status status;

    clear_stdout();

    for(counter = 0; counter < 3; counter++) {
        status = pop(&intarray[counter]);
        if (status != SUCCESS) {
            break;
        }
        char ausgabe[TEXT_LENGTH];
        sprintf(ausgabe, "%d\n", intarray[counter]);
        print_stdout(ausgabe);
    }

    if(counter == 0)
    {
        return EMPTY_STACK;
    }
    counter -= 1;
    for (; counter >= 0; counter--) {
        push(intarray[counter]);
    }
    return SUCCESS;

}



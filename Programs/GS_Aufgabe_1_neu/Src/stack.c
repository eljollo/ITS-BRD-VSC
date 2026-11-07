/**
 * @file stack.c
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Oct 2026
 *
 * @brief This module implements a a stack for stack-operations.
 */

#include "stack.h"
#include "error_handling.h"

// Konstanten
#define STACK_SIZE 20 // size of the stack aka max number of elements in stack

// Variablen
static int stackpointer;
static int stack[STACK_SIZE];

// reset stack
// muss hier auch noch die fehlermeldung resettet werden? (siehe Aufgabenblatt
// Seite 2)
void init_stack(void) { stackpointer = -1; }

// push value on stack
enum Status push(int val) {
   if (stackpointer < STACK_SIZE - 1) {
      stackpointer++;
      stack[stackpointer] = val;
      return SUCCESS;
   }
   return STACK_OVERFLOW;
}

// pop value from stack
enum Status pop(int *val) {
   if (stackpointer > -1) {
      *val = stack[stackpointer];
      stackpointer--;
      return SUCCESS;
   }
   return STACK_UNDERFLOW;
}


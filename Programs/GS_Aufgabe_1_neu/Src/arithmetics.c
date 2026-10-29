/**
 * @file arithmetics.c
 * @author Lasse Bruhn, Matr.Num.: 2880211
 * @date Oct 2026
 *
 * @brief contains the implementations of the arithmetic functions add,
 * subtract, multiply and divide.
 */

#include "arithmetics.h"
#include "error_handling.h"
#include "stack.h"
#include <limits.h>
// #include <stdlib.h>

enum Status add(void) {
   int operand1 = 0;
   int operand2 = 0;

   enum Status status = pop(&operand1); // pops value to the address of operand1
   if (status != SUCCESS) {
      return status;
   }
   status = pop(&operand2); // wert auf den der stackpointer zeigt, wird an adresse von operand2 gespeichert
   if (status != SUCCESS) {
      return status;
   }

   // check for overflow
   if (operand1 > 0 && operand2 > 0 && operand1 > (INT_MAX - operand2)) {
      return ARITH_OVERFLOW;
   }
   if (operand1 < 0 && operand2 < 0 && operand1 < (INT_MIN - operand2)) {
      return ARITH_OVERFLOW;
   }

   int result = operand1 + operand2;
   push(result);
   return SUCCESS;
}

enum Status subtract(void) {
   int operand1 = 0;
   int operand2 = 0;

   enum Status status =
       pop(&operand1); // pops value to the address of operand1
   if (status != SUCCESS) {
      return status;
   }
   status =
       pop(&operand2); // wert auf den der stackpointer zeigt, wird an
                                 // adresse von operand2 gespeichert
   if (status != SUCCESS) {
      return status;
   }

   /*overflow checks*/
   if (operand2 > 0 && operand1 < 0 && operand2 > (INT_MAX + operand1)) {
      return ARITH_OVERFLOW;
   }
   if (operand2 < 0 && operand1 > 0 && operand2 < (INT_MIN + operand1)) {
      return ARITH_OVERFLOW;
   }

   int result = operand2 - operand1;
   push(result);
   return SUCCESS;
}

enum Status multiply(void) {
   int operand1 = 0;
   int operand2 = 0;

   enum Status status =
       pop(&operand1); // pops value to the address of operand1
   if (status != SUCCESS) {
      return status;
   }
   status = pop(&operand2); // wert auf den der stackpointer zeigt,
                                     // wird an adresse von operand2 gespeichert
   if (status != SUCCESS) {
      return status;
   }

   /*overflow checks*/
   if (operand1 > 0 && operand2 > 0 && operand1 > INT_MAX / operand2) {
      return ARITH_OVERFLOW;
   }
   if (operand1 > 0 && operand2 < 0 && operand2 < INT_MIN / operand1) {
      return ARITH_OVERFLOW;
   }
   if (operand1 < 0 && operand2 > 0 && operand1 < INT_MIN / operand2) {
      return ARITH_OVERFLOW;
   }
   if (operand1 < 0 && operand2 < 0 && operand1 < INT_MAX / operand2) {
      return ARITH_OVERFLOW;
   }

   int result = operand1 * operand2;
   push(result);
   return SUCCESS;
}

enum Status divide(void) {
   int operand1 = 0;
   int operand2 = 0;

   enum Status status = pop(&operand1); // pops value to the address of operand1
   if (status != SUCCESS) {
      return status;
   }
   status = pop(&operand2); // pops value to the address of operand2
   if (status != SUCCESS) {
      return status;
   }

   /*overflow checks*/
   if (operand1 == 0) { // check for division by zero
      return DIV_BY_ZERO;
   }
   if (operand2 == INT_MIN && operand1 == -1) { // check for overflow
      return ARITH_OVERFLOW;
   }

   int result = operand2 / operand1;
   push(result);
   return SUCCESS;
}

// double
enum Status funct_d(void) {
    int operand1 = 0;

   enum Status status = pop(&operand1); // pops value to the address of operand1
   if (status != SUCCESS) {
      return status;
   }
   status = push(operand1);
   if (status != SUCCESS) {
      return status;
   }
   status = push(operand1);
   if (status != SUCCESS) {
      return status;
   }
}


// reverse
enum Status funct_r(void) {
    int operand1 = 0;
    int operand2 = 0;

    enum Status status = pop(&operand1); // pops value to the address of operand1
    if (status != SUCCESS) {
       return status;
    }
    status = pop(&operand2); // pops value to the address of operand1
   if (status != SUCCESS) {
      return status;
   }
   status = push(operand2);
   if (status != SUCCESS) {
      return status;
   }
   status = push(operand1);
   if (status != SUCCESS) {
      return status;
   }
}

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
#define STACK_SIZE 20   // size of the stack aka max number of elements in stack

// Globale Variablen
static int stackpointer;
static int stack[STACK_SIZE];

// reset stack
// muss hier auch noch die fehlermeldung resettet werden? (siehe Aufgabenblatt Seite 2)
void init_stack(void){
    stackpointer = -1;
}

// push value on stack
enum Status push(int val){
    if (stackpointer < STACK_SIZE-1){
        stackpointer ++ ;
        stack[stackpointer] = val ;
        return SUCCESS;
    }
    return STACK_OVERFLOW;
}

// pop value from stack
enum Status pop(int *val){
   if(stackpointer > -1){
       *val = stack[stackpointer];
       stackpointer -- ;
       return SUCCESS;
   }
   return STACK_UNDERFLOW;
}

// Funktion p (druckt den obersten Wert des Stacks aus, ohne dass der Stack verändert wird)
enum Status funct_p(int *val){
    if(stackpointer > -1){
       *val = stack[stackpointer];
       return SUCCESS;
   }
    return EMPTY_STACK;
}

// Funktion P (druckt die drei obersten Werte des Stacks aus)
enum Status funct_pthree(int *elem_counter, int values[3]){
    *elem_counter = 0;
    if(stackpointer > -1){
        int sp_tmp = stackpointer;
        while (sp_tmp > -1 && *elem_counter < 3) {
           values[*elem_counter] = stack[sp_tmp];
           sp_tmp --;
           (*elem_counter) ++;
        }
       return SUCCESS;
   }
    return EMPTY_STACK;
}

// Funktion d (dupliziert den obersten Eintrag des Stacks)
enum Status funct_d(void){
    if (stackpointer < STACK_SIZE -1) {
        stackpointer ++ ;
        stack[stackpointer] = stack[stackpointer-1] ;
        return SUCCESS;   
    }
    return STACK_OVERFLOW;
}

// Funktion r (vertauscht die Reihenfolge der beiden obersten Einträge des Stacks)
enum Status funct_r(void){
    if (stackpointer >= 1) {
        int tmp = stack[stackpointer];
        stack[stackpointer] = stack[stackpointer-1];
        stack[stackpointer-1] = tmp;
        return SUCCESS;
    }
    return STACK_UNDERFLOW;
}
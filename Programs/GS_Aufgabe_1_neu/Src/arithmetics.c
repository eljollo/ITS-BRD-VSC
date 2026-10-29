/**
* @file arithmetics.c
* @author Lasse Bruhn, Matr.Num.: 2880211
* @date Oct 2026
*
* @brief contains the implementations of the arithmetic functions add, subtract, multiply and divide.
*/

#include "arithmetics.h"
#include "error_handling.h"
#include "stack.h"
#include <limits.h>
// #include <stdlib.h>

enum Status add(void){
    int operand1 = 0;
    int* address_of_operand1 = &operand1; //holds the address of the variable operand1
    int operand2 = 0;
    int* address_of_operand2 = &operand2; 

    enum Status status = pop(address_of_operand1); 
    if (status != SUCCESS) {
        return status;
    }
    status = pop(address_of_operand2); 
    if (status != SUCCESS) {
        return status;
    }
    
    //check for overflow
    if (operand1 > 0 && operand2 > 0 && operand1 > (INT_MAX - operand2)){
        return ARITH_OVERFLOW;
    }
    if (operand1 < 0 && operand2 < 0 && operand1 < (INT_MIN - operand2)){
        return ARITH_OVERFLOW;
    }

    int result = operand1 + operand2;
    push(result);
    return SUCCESS;
}

enum Status subtract(void){
    int operand1 = 0;
    int* address_of_operand1 = &operand1; //holds the address of the variable operand1
    int operand2 = 0;
    int* address_of_operand2 = &operand2; //holds the address of the variable operand2

    enum Status status = pop(address_of_operand1); //pops value to the address of operand1
    if (status != SUCCESS) {
        return status;
    }
    status = pop(address_of_operand2); //wert auf den der stackpointer zeigt, wird an adresse von operand2 gespeichert
    if (status != SUCCESS) {
        return status;
    }

    /*overflow checks*/
    if (operand2 > 0 && operand1 < 0 && operand2 > (INT_MAX + operand1)){
        return ARITH_OVERFLOW;
    }
    if (operand2 < 0 && operand1 > 0 && operand2 < (INT_MIN + operand1)){
        return ARITH_OVERFLOW;
    }

    int result = operand2 - operand1;
    push(result);
    return SUCCESS;
}

enum Status multiply(void){
    int operand1 = 0;
    int* adress_of_operand1 = &operand1; //holds the address of the variable operand1
    int operand2 = 0;
    int* adress_of_operand2 = &operand2; //holds the address of the variable operand2

    enum Status status = pop(adress_of_operand1); //pops value to the address of operand1
    if (status != SUCCESS) {
        return status;
    }
    status = pop(adress_of_operand2); //wert auf den der stackpointer zeigt, wird an adresse von operand2 gespeichert
    if (status != SUCCESS) {
        return status;
    }

    /*overflow checks*/
    if (operand1 > 0 && operand2 > 0 && operand1 > INT_MAX / operand2){
        return ARITH_OVERFLOW;
    }
    if (operand1 > 0 && operand2 < 0 && operand2 < INT_MIN / operand1){
        return ARITH_OVERFLOW;
    }
    if (operand1 < 0 && operand2 > 0 && operand1 < INT_MIN / operand2){
        return ARITH_OVERFLOW;
    }
    if (operand1 < 0 && operand2 < 0 && operand1 < INT_MAX / operand2){
        return ARITH_OVERFLOW;
    }

    int result = operand1 * operand2;
    push(result);
    return SUCCESS;
}

enum Status divide(void){
    int operand1 = 0;
    int* adress_of_operand1 = &operand1; //holds the address of the variable operand1
    int operand2 = 0;
    int* adress_of_operand2 = &operand2; //holds the address of the variable operand2

    enum Status status = pop(adress_of_operand1);  
    if (status != SUCCESS) {
        return status;
    }
    status = pop(adress_of_operand2); //pops value to the address of operand2
    if (status != SUCCESS) {
        return status;
    }

    /*overflow checks*/
    if(operand1 == 0){  //check for division by zero
        return DIV_BY_ZERO;
    }
    if (operand2 == INT_MIN && operand1 == -1){ //check for overflow
        return ARITH_OVERFLOW;
    }
    
    int result = operand2 / operand1;
    push(result);
    return SUCCESS;
}
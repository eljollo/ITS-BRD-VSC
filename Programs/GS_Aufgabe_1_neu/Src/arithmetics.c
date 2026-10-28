#include "arithmetics.h"
#include "error_handling.h"
#include "stack.h"
#include <limits.h>
#include <stdlib.h>

enum Status arith_add(void){
    int operand1 = 0;
    int* address_of_operand1 = &operand1; //holds the address of the variable operand1
    int operand2 = 0;
    int* address_of_operand2 = &operand2; 

    pop(address_of_operand1); 
    pop(address_of_operand2); 
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

enum Status arith_sub(void){
    int operand1 = 0;
    int* address_of_operand1 = &operand1; //holds the address of the variable operand1
    int operand2 = 0;
    int* address_of_operand2 = &operand2; //holds the address of the variable operand2

    pop(address_of_operand1); //pops value to the address of operand1
    pop(address_of_operand2); //wert auf den der stackpointer zeigt, wird an adresse von operand2 gespeichert

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

enum Status arith_mul(void){
    int operand1 = 0;
    int* adress_of_operand1 = &operand1; //holds the address of the variable operand1
    int operand2 = 0;
    int* adress_of_operand2 = &operand2; //holds the address of the variable operand2

    pop(adress_of_operand1); //pops value to the address of operand1
    pop(adress_of_operand2); //wert auf den der stackpointer zeigt, wird an adresse von operand2 gespeichert

    /*overflow checks*/
    if (operand1 > 0 && operand2 > 0 && abs(operand1) > (abs(INT_MAX) / operand2)){
        return ARITH_OVERFLOW;
    }
    if (operand1 > 0 && operand2 < 0 && abs(operand1) > (abs(INT_MIN) / abs(operand2))){
        return ARITH_OVERFLOW;
    }
    if (operand1 < 0 && operand2 > 0 && abs(operand1) > (abs(INT_MIN) / abs(operand2))){
        return ARITH_OVERFLOW;
    }
    if (operand1 < 0 && operand2 < 0 && abs(operand1) > (abs(INT_MAX) / abs(operand2))){
        return ARITH_OVERFLOW;
    }

    int result = operand1 * operand2;
    push(result);
    return SUCCESS;
}

enum Status arith_div(void){
    int operand1 = 0;
    int* adress_of_operand1 = &operand1; //holds the address of the variable operand1
    int operand2 = 0;
    int* adress_of_operand2 = &operand2; //holds the address of the variable operand2

    pop(adress_of_operand1);  
    pop(adress_of_operand2); //pops value to the address of operand2

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
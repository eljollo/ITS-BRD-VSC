#include "arith_sub.h"
#include "error_handling.h"
#include "stack.h"
#include <limits.h>

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
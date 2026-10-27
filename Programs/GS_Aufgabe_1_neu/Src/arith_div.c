#include "arith_div.h"
#include "error_handling.h"
#include "stack.h"
#include <limits.h>

int arith_div(void){
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
    return 0;
}
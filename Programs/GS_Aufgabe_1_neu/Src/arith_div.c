#include "arith_div.h"
#include "error_handling.h"
#include "stack.h"

int arith_div(void){
    int operand1 = 0;
    int* adress_of_operand1 = &operand1; 
    int operand2 = 0;
    int* adress_of_operand2 = &operand2; 
    pop(adress_of_operand1);  
    if(operand1 == 0){
        return -1;
    } //check if the divisor is 0 for error handling
    pop(adress_of_operand2); //pops value to the address of operand2
    int result = operand2 / operand1;
    push(result);
    return 0;
}
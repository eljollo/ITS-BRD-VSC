#include "arith_add.h"
#include "error_handling.h"
#include "stack.h"

int arith_add(void){
    int operand1 = 0;
    int* address_of_operand1 = &operand1; //holds the address of the variable operand1
    int operand2 = 0;
    int* address_of_operand2 = &operand2; 
    pop(address_of_operand1); 
    pop(address_of_operand2); 
    //check for overflow
}
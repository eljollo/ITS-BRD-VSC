#include "arith_sub.h"
#include "error_handling.h"
#include "stack.h"

int arith_sub(void){
    int operand1 = pop(&operand1);
    int operand2 = pop(&operand2);
    int result = operand2 - operand1;
    push(result);
    return 0;
}
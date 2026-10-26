#include "arith_mul.h"
#include "error_handling.h"
#include "stack.h"

int arith_mul(void){
    int operand1 = 0;
    int* adress_of_operand1 = &operand1; //holds the address of the variable operand1
    int operand2 = 0;
    int* adress_of_operand2 = &operand2; //holds the address of the variable operand2
    pop(adress_of_operand1); //pops value to the address of operand1
    pop(adress_of_operand2); //wert auf den der stackpointer zeigt, wird an adresse von operand2 gespeichert
    int result = operand2 * operand1;
    push(result);
    return 0;
}
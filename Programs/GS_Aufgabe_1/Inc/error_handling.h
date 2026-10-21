#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H
// enum to cover error codes of functions return value
enum Status {
    SUCCESS,            // successfull operation
    DIV_BY_ZERO,        // Division durch Null
    ARITH_OVERFLOW,     // Bereichsüberschreitung arith. Operationen
    STACK_OVERFLOW,     // Stack Overflow
    STACK_UNDERFLOW,    // Stack Underflow
};
#endif
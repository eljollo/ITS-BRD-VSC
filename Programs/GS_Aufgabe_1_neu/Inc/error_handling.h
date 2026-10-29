/**
 * @file error_handling.h
 * @author Thomas Ramba, Matr.Num.: 284259
 * @date Oct 2026
 * @brief File for declaration of error messages.
 */

#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H
// enum to cover error codes of functions return value
enum Status {
   SUCCESS,         // successfull operation
   DIV_BY_ZERO,     // Division durch Null
   ARITH_OVERFLOW,  // Bereichsüberschreitung arith. Operationen
   STACK_OVERFLOW,  // Stack Overflow
   STACK_UNDERFLOW, // Stack Underflow
   EMPTY_STACK, // Stack empty (e.g. function p or function P when no element on
                // stack)
};


#endif
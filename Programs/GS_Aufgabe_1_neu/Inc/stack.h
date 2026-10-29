/**
 * @file stack.c
 * @author Thomas Ramba, Matr.Num.: 284259
 * @date Oct 2026
 *
 * @brief This file contains the header file of the stack module.
 */

/**
 **********************************************************************
 *
 * @brief Initialisiert den Stack samt Stackpointer
 *
 **********************************************************************/
extern void init_stack(void);

/**
 **********************************************************************
 *
 * @brief Fuegt ein Element in die Menge ein.
 *
 * @param XXX
 *
 * @return XXX
 **********************************************************************/
extern enum Status push(int val);

/**
 **********************************************************************
 *
 * @brief XXX.
 *
 * @param XXX
 *
 * @return XXX
 **********************************************************************/
extern enum Status pop(int *val);

/**
 **********************************************************************
 *
 * @brief XXX
 *
 * @param XXX
 *
 * @return XXX
 **********************************************************************/
extern enum Status funct_p(int *val);

/**
 **********************************************************************
 *
 * @brief XXX
 *
 * @param XXX
 *
 * @return XXX
 **********************************************************************/
extern enum Status funct_pthree(int *elem_counter, int values[3]);

/**
 **********************************************************************
 *
 * @brief XXX
 *
 * @param XXX
 *
 * @return XXX
 **********************************************************************/
extern enum Status funct_d(void);

/**
 **********************************************************************
 *
 * @brief XXX
 *
 * @param XXX
 *
 * @return XXX
 **********************************************************************/
extern enum Status funct_r(void);

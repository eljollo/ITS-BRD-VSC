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
 * @brief sets the stackpointer to -1, so that the stack is empty
 *
 **********************************************************************/
extern void init_stack(void);

/**
 **********************************************************************
 *
 * @brief legt einen Wert als oberstes Element auf den Stack.
 *
 * @param val ist der übergebene / eingegebene Wert
 *
 * @return status ob erfolgreich oder overflow
 **********************************************************************/
extern enum Status push(int val);

/**
 **********************************************************************
 *
 * @brief gibt den obersten wert vom stack zurück und löscht diesen (verschiebt
 *den stackpointer eins nach unten).
 *
 * @param *val adresse um Stackwert zu speichern
 *
 * @return status ob erfolgreich oder overflow
 **********************************************************************/
extern enum Status pop(int *val);

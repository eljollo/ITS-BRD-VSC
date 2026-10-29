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
 * @brief gibt den obersten wert vom stack zurück und löscht diesen (verschiebt den stackpointer eins nach unten).
 *
 * @param *val adresse um Stackwert zu speichern
 *
 * @return status ob erfolgreich oder overflow
 **********************************************************************/
extern enum Status pop(int *val);

/**
 **********************************************************************
 *
 * @brief druckt den obersten Wert des Stacks auf das Display ohne den Stack zu verändern.
 *
 * @param *val adresse um Stackwert zu speichern
 *
 * @return status ob erfolgreich oder overflow
 **********************************************************************/
extern enum Status funct_p(int *val);

/**
 **********************************************************************
 *
 * @brief druckt die bis zu 3 obersten Werte des Stacks auf das Display ohne den Stack zu verändern
 *
 * @param *elem_counter zählt wie viele elemente vom stack gelesen werden, das array values[3] speichert die Werte, die vom stack gelesen werden
 *
 * @return status ob erfolgreich oder overflow
 **********************************************************************/
extern enum Status funct_pthree(int *elem_counter, int values[3]);

/**
 **********************************************************************
 *
 * @brief legt den Wert vom stack erneut auf den stack
 *
 * @param void
 *
 * @return status ob erfolgreich oder overflow
 **********************************************************************/
extern enum Status funct_d(void);

/**
 **********************************************************************
 *
 * @brief vertauscht die obersten beiden Werte vom stack
 *
 * @param XXX
 *
 * @return status ob erfolgreich oder overflow
 **********************************************************************/
extern enum Status funct_r(void);

/**
 **********************************************************************
 *
 * @brief 
 *
 **********************************************************************/
extern void init(void);

/**
 **********************************************************************
 *
 * @brief Fuegt ein Element in die Menge ein.
 *
 * @param val Element, das eingefuegt wird
 *
 * @return Bei einem Fehler -1 ansonsten 0
 **********************************************************************/
extern enum Status push(int val);

/**
 **********************************************************************
 *
 * @brief Fuegt ein Element in die Menge ein.
 *
 * @param val* Pointer, der auf die Variable zeigt, in die der Wert vom Stack geschrieben wird
 *
 * @return Bei einem Fehler -1 ansonsten 0
 **********************************************************************/
extern enum Status pop(int *val);

/**
 **********************************************************************
 *
 * @brief Fuegt ein Element in die Menge ein.
 *
 * @param val Element, das eingefuegt wird
 *
 * @return Bei einem Fehler -1 ansonsten 0
 **********************************************************************/
extern enum Status p_show(int *val);

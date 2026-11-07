/**
 **********************************************************************
 *
 * @file arithmetics.h
 *
 * @brief Header-Datei für die arithmetischen Operationen des Moduls
 *arithmetics.
 *
 * @author Lasse Bruhn, Matr.-Nr.: 2880211
 *
 * @date 2024-06-10
 *
 **********************************************************************
 */

/**
 **********************************************************************
 *
 * @brief Nimmt 2 Elemente vom Stack und addiert beide Elemente.
        Pusht das Ergebnis wieder auf den Stack.
 * @param void
 *
 * @return Bei einem Fehler den entsprechenden Fehlercode(siehe
 error_handling.h) ansonsten SUCCESS
 **********************************************************************/
extern enum Status add(void);

/**
 **********************************************************************
 *
 * @brief Nimmt 2 Elemente vom Stack und subtrahiert erstes(oberstes) Element
 vom zweiten Element. Pusht das Ergebnis wieder auf den Stack.
 * @param void
 *
 * @return Bei einem Fehler den entsprechenden Fehlercode(siehe
 error_handling.h) ansonsten SUCCESS
 **********************************************************************/
extern enum Status subtract(void);

/**
 **********************************************************************
 *
 * @brief Nimmt 2 Elemente vom Stack und multipliziert beide Elemente.
        Pusht das Ergebnis wieder auf den Stack.
 * @param void
 *
 * @return Bei einem Fehler den entsprechenden Fehlercode(siehe
 error_handling.h) ansonsten SUCCESS
 **********************************************************************/
extern enum Status multiply(void);

/**
 **********************************************************************
 *
 * @brief Nimmt 2 Elemente vom Stack und dividiert das zweite durch das erste.
        Pusht das Ergebnis wieder auf den Stack.
 * @param void
 *
 * @return Bei einem Fehler den entsprechenden Fehlercode(siehe
 error_handling.h) ansonsten SUCCESS
 **********************************************************************/
extern enum Status divide(void);


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

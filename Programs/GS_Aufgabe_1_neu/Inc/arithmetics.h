/**
 **********************************************************************
 *
 * @file arithmetics.h
 *
 * @brief Header-Datei für die arithmetischen Operationen.
 *
 * @author Lasse
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
 * @return Bei einem Fehler den entsprechenden Fehlercode(siehe error_handling.h) ansonsten SUCCESS
 **********************************************************************/
extern enum Status arith_add();

/**
 **********************************************************************
 *
 * @brief Nimmt 2 Elemente vom Stack und subtrahiert erstes(oberstes) Element vom
        zweiten Element. Pusht das Ergebnis wieder auf den Stack.
 * @param void
 *
 * @return Bei einem Fehler den entsprechenden Fehlercode(siehe error_handling.h) ansonsten SUCCESS
 **********************************************************************/
extern enum Status arith_sub();

/**
 **********************************************************************
 *
 * @brief Nimmt 2 Elemente vom Stack und multipliziert beide Elemente. 
        Pusht das Ergebnis wieder auf den Stack.
 * @param void
 *
 * @return Bei einem Fehler den entsprechenden Fehlercode(siehe error_handling.h) ansonsten SUCCESS
 **********************************************************************/
extern enum Status arith_mul();

/**
 **********************************************************************
 *
 * @brief Nimmt 2 Elemente vom Stack und dividiert das zweite durch das erste. 
        Pusht das Ergebnis wieder auf den Stack.
 * @param void
 *
 * @return Bei einem Fehler den entsprechenden Fehlercode(siehe error_handling.h) ansonsten SUCCESS
 **********************************************************************/
 extern enum Status arith_div(); 
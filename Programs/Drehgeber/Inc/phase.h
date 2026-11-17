/**
 * @file phase.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief .
 */

 #ifndef PHASE_H
#define PHASE_H

#include <stdbool.h>
#include "structs.h"


// Konstanten
#define ERROR 99

// struct als datentyp für Zustand der Phase
typedef struct {
    Phase previous;
    bool has_previous;

    int64_t phase_counter;
    
    uint64_t last_change_ticks; // für phasenwechsel und phasenzähler gleich
    bool has_last_change;       // gab es seit reset einen gültigen phassenwechsel

    uint64_t change_number;     // anzahl an phasenwechsel (richtungsunabhängig)

    Direction last_direction;
    bool error;
} PhaseState;
// Variable um Zustand festzuhalten

/**
  ****************************************************************************** 
  * @author  Thomas Ramba, Matr.Num.: 2842594
  * @brief   . 
  ******************************************************************************
  */
void phase_reset(PhaseState *state);

/**
  ****************************************************************************** 
  * @author  Thomas Ramba, Matr.Num.: 2842594
  * @brief   Nimmt jeweils aktuell verwendete Phase und PhaseState entgegen und setzt Werte von state entsprechend der 
             Werte von current
  ******************************************************************************
  */
void phase_process(Phase current, PhaseState state);

/**
  ****************************************************************************** 
  * @author  Thomas Ramba, Matr.Num.: 2842594
  * @brief   . 
  * @return  .
  ******************************************************************************
  */
bool phase_has_error(PhaseState state);

/**
  ****************************************************************************** 
  * @author  Thomas Ramba, Matr.Num.: 2842594
  * @brief   . 
  * @return  .
  ******************************************************************************
  */
Direction phase_get_last_direction(PhaseState state);

/**
  ****************************************************************************** 
  * @author  Thomas Ramba, Matr.Num.: 2842594
  * @brief   . 
  * @return  .
  ******************************************************************************
  */
PhaseCountSnapshot phase_get_counter_sample(PhaseState state);

#endif
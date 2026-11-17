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
#include <stdint.h>

// Konstanten
#define ERROR_CODE 99

// struct als datentyp für inhalt / informationen der Phase
typedef struct {
   uint8_t phase_bits;
   uint64_t timer_ticks;
} Phase;

// enum für direction
typedef enum {
   DIRECTION_UNKNOWN = 0,
   DIRECTION_FORWARD,
   DIRECTION_BACKWARD,
} Direction;

// struct als datentyp für Zustand der Phase
typedef struct {
   Phase previous;
   bool has_previous;

   int64_t phase_counter;

   uint64_t last_change_ticks; // für phasenwechsel und phasenzähler gleich
   bool has_last_change; // gab es seit reset einen gültigen phassenwechsel

   uint64_t change_number; // anzahl an phasenwechsel (richtungsunabhängig)

   Direction last_direction;
   bool error;
} PhaseState;

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 * @return  .
 ******************************************************************************
 */
// KOPIE der zählerzustände für berechnungen
typedef struct {
   int64_t count;          // = phasenzähler
   uint64_t change_ticks;  // zeitpunkt letzter gültiger wechsel
   uint64_t change_number; // zähöer für alle wechsel seit start / reset
   bool has_last_change;   // s.o. gab es gültigern Phasenwechsel
} PhaseCountSnapshot;

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 ******************************************************************************
 */
void phase_reset();

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 ******************************************************************************
 */
void phase_process(Phase current);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 * @return  .
 ******************************************************************************
 */
bool phase_has_error(void);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 * @return  .
 ******************************************************************************
 */
Direction phase_get_last_direction(void);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 * @return  .
 ******************************************************************************
 */
PhaseCountSnapshot phase_get_counter_sample(void);

#endif
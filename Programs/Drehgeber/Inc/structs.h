/**
 * @file structs.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief .
 */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>
#include <stdint.h>

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 * @return  .
 ******************************************************************************
 */
// struct als datentyp für inhalt / informationen der Phase
typedef struct {
   uint8_t phase_bits;
   uint64_t timer_ticks;
} Phase;

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 * @return  .
 ******************************************************************************
 */
// enum für direction
typedef enum {
   DIRECTION_UNKNOWN = 0,
   DIRECTION_FORWARD,
   DIRECTION_BACKWARD,
} Direction;

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

#endif
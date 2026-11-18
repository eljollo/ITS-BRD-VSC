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

// enum für direction
typedef enum {
   DIRECTION_UNKNOWN = 0,
   DIRECTION_FORWARD,
   DIRECTION_BACKWARD,
} Direction;

typedef struct {
   int64_t phase_counter;  // = phasenzähler
   uint64_t change_ticks;  // zeitpunkt letzter gültiger wechsel
   uint64_t total_changes; // zähöer für alle wechsel seit start / reset
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
void phase_process(uint8_t phase_bits, uint64_t timer_ticks);

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
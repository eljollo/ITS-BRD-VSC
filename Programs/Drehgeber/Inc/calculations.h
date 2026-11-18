/**
 * @file calculations.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief .
 */

#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "phase.h"
#include <stdbool.h>
#include <stdint.h>

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 * @return  .
 ******************************************************************************
 */
double calculate_angle(int64_t phase_count);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 * @return  Gibt false zurück, wenn noch keine berechenbare Zeitspanne vorliegt.
 ******************************************************************************
 */
double calculate_speed(PhaseCountSnapshot start, PhaseCountSnapshot end);

#endif
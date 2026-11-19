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

typedef struct {
   double angle;
   double speed;
} CalcOutput;

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   Berechnet Winkel.
 * @return  gibt Wert für Winkel zurück.
 ******************************************************************************
 */
double calculate_angle(int64_t phase_count);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   Berechnet Winkelgeschwindigkeit.
 * @return  gibt Wert für Winkelgeschwindigkeit zurück.
 ******************************************************************************
 */
double calculate_speed(PhaseCountSnapshot start, PhaseCountSnapshot end);

#endif
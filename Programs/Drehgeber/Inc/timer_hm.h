/**
 * @file timer.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief .
 */

#ifndef TIMER_HM_H
#define TIMER_HM_H

#include <stdint.h>

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   setzt die lokalen timer-Variablen zurück.
 ******************************************************************************
 */
void timer_reset_extension(void);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   erweitert die gelesenen timer_ticks von 32 auf 64 Bit.
 * @return  gibt erweiterten Timerstand zurück.
 ******************************************************************************
 */
uint64_t timer_extend(uint32_t raw_ticks);

#endif
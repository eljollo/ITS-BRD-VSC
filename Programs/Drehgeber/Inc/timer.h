/**
 * @file timer.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief .
 */

 #ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/**
  ****************************************************************************** 
  * @author  Thomas Ramba, Matr.Num.: 2842594
  * @brief   . 
  * @return  .
  ******************************************************************************
  */
void timer_reset_extension(void);

/**
  ****************************************************************************** 
  * @author  Thomas Ramba, Matr.Num.: 2842594
  * @brief   . 
  * @return  .
  ******************************************************************************
  */
uint64_t timer_extend(uint32_t raw_ticks);

#endif
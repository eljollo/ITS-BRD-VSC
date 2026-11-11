/**
 * @file display.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief .
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

/**
  ****************************************************************************** 
  * @author  Thomas Ramba, Matr.Num.: 2842594
  * @brief   . 
  ******************************************************************************
  */
void display_init(void);

/**
  ****************************************************************************** 
  * @author  Thomas Ramba, Matr.Num.: 2842594
  * @brief   . 
  ******************************************************************************
  */
void display_reset_pending(void);

/**
  ****************************************************************************** 
  * @author  Thomas Ramba, Matr.Num.: 2842594
  * @brief   . 
  ******************************************************************************
  */
void display_queue_values(double angle, bool speed_valid, double speed);

/**
  ****************************************************************************** 
  * @author  Thomas Ramba, Matr.Num.: 2842594
  * @brief   . 
  ******************************************************************************
  */
void display_step(void);

#endif
/**
 * @file led_output.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief Steuert den Output (Ein & Aus) der LEDs auf dem ITS-Board.
 */

#ifndef LED_OUTPUT_H
#define LED_OUTPUT_H

// ============ INCLUDES ============
#include "phase.h"
#include <stdbool.h>

// ============ KONSTANTEN ============
/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   setzt LED outputs auf dem ITS Board bzgl. Richtungsanzeige,
 * Error-Fall und Anzahl Phasenwechsel.
 ******************************************************************************
 */
void set_all_output(Direction direction, bool error, int64_t phase_changes);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   Setzt alle LEDs auf Null.
 ******************************************************************************
 */
void reset_all_leds();

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   Setzt Error-LED.
 ******************************************************************************
 */
void set_gpioe_error(bool error);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   Setzt LED Pin für Oszilloskopmessung auf 1.
 ******************************************************************************
 */
void set_pin_for_oszilloskop();

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   Setzt LED Pin für Oszilloskopmessung auf 0.
 ******************************************************************************
 */
void reset_pin_for_oszilloskop();

#endif

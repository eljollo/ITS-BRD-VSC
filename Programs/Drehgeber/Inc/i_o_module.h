/**
 * @file i_o_module.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief .
 */

#ifndef IO_H
#define IO_H

#include "phase.h"
#include <stdbool.h>
#include <stdint.h>

// ============ KONSTANTEN ============
// für Displayausgabe
#define BUFF_SIZE 16
#define X_START_WRITE 1
#define Y_COORD_WRITE_ANGLE 3
#define Y_COORD_WRITE_SPEED 5
#define X_OFFSET_WRITE_ANGLE 30
#define X_OFFSET_WRITE_SPEED 30
#define MAX_INDEX 8

extern char angle_buff[BUFF_SIZE];
extern char speed_buff[BUFF_SIZE];

// struct für input
typedef struct {
   bool reset_pressed;   // Zustand von S6
   uint8_t phase_bits;   // Kodierung: (A << 1) | B
   uint64_t timer_ticks; // auf 64 Bit erweiterter Wert des timers
} IoInputs;

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   Printet initialen Inhalt auf Display.
 ******************************************************************************
 */
void init_display_output();

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   setzt Werte auf Display zurück auf 0.0 (Default).
 ******************************************************************************
 */
void reset_display();

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   printet je Superloop ein Zeichen auf das Display sofern Änderung zu
 * vorheriger Ziffer.
 ******************************************************************************
 */
void display_update(double angle, double speed);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   liest alle relevanten Eingänge und speichert sie in IoInputs struct.
 ******************************************************************************
 */
void read_all_inputs(IoInputs *input);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 ******************************************************************************
 */
void set_all_output(Direction direction, bool error, int64_t phase_changes);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 ******************************************************************************
 */
void reset_all_leds();

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 ******************************************************************************
 */
void set_gpioe_error(bool error);

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 ******************************************************************************
 */
void set_pin_for_oszilloskop();

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   .
 ******************************************************************************
 */
void reset_pin_for_oszilloskop();

#endif
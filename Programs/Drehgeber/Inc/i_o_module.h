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
#define X_OFFSET_WRITE_ANGLE 10
#define X_OFFSET_WRITE_SPEED 10
#define MAX_INDEX 8

extern char angle_buff[BUFF_SIZE];
extern char speed_buff[BUFF_SIZE];

// für Hardware IO Bitoperationen
#define ODR_MASK_PIN_0 (0x01U << 0) // drehgeber IN0 -> PF0
#define ODR_MASK_PIN_1 (0x01U << 1) // drehgeber IN1 -> PF1
#define ODR_MASK_PIN_5 (0x01U << 5) // error
#define ODR_MASK_PIN_6 (0x01U << 6) // backward | reset button
#define ODR_MASK_PIN_7 (0x01U << 7) // forward
#define ODR_MASK_ALL 0xFF

// struct für input
typedef struct {
   bool reset_pressed;       // Zustand von S6
   uint8_t phase_bits;       // Kodierung: (A << 1) | B
   uint32_t raw_timer_ticks; // Rohwert des 32-Bit-Hardwaretimers
} IoInputs;

void init_display_output();

void display_update();

void read_all_inputs(IoInputs *input);

void set_all_output(Direction direction, bool error, uint64_t phase_changes);

void reset_all_leds();

void set_gpioe_error(bool error);
// ####################################################
// ####################################################
// ####################################################

#endif
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
#define X_OFFSET_WRITE_ANGLE 20
#define X_OFFSET_WRITE_SPEED 20
#define MAX_INDEX 8

extern char angle_buff[BUFF_SIZE];
extern char speed_buff[BUFF_SIZE];

// struct für input
typedef struct {
   bool reset_pressed;       // Zustand von S6
   uint8_t phase_bits;       // Kodierung: (A << 1) | B
   uint32_t raw_timer_ticks; // Rohwert des 32-Bit-Hardwaretimers
} IoInputs;

void init_display_output();

void display_update(double angle, double speed);

void read_all_inputs(IoInputs *input);

void set_all_output(Direction direction, bool error, int64_t phase_changes);

void reset_all_leds();

void set_gpioe_error(bool error);

void set_pin_for_oszilloskop();

void reset_pin_for_oszilloskop();
// ####################################################
// ####################################################
// ####################################################

#endif
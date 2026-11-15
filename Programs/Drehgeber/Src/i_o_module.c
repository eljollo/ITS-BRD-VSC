/**
 ******************************************************************************
 * @file    i_o_module.c
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief   enthält Definitionen, bzw. Implementierungen der in i_o_module.h
 * deklarierten Funktionen
 ******************************************************************************
 */

// ============ INLCUDES ============
#include "i_o_module.h"
#include "lcd.h"
#include "stm32f429xx.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "structs.h"
#include "timer.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// ============ KONSTANTEN ============
#define BUFF_SIZE 16
#define X_START_WRITE 1
#define Y_COORD_WRITE_ANGLE 3
#define Y_COORD_WRITE_SPEED 5
#define X_OFFSET_WRITE_ANGLE 10
#define X_OFFSET_WRITE_SPEED 10
#define MAX_INDEX 8

// ============ Display init ============
void init_display_output(void) {
   lcdGotoXY(X_START_WRITE, Y_COORD_WRITE_ANGLE);
   lcdPrintlnS("Winkel:");
   lcdGotoXY(X_START_WRITE, Y_COORD_WRITE_SPEED);
   lcdPrintlnS("Geschwindigkeit:");
   lcdGotoXY(X_OFFSET_WRITE_ANGLE + BUFF_SIZE, Y_COORD_WRITE_ANGLE);
   lcdPrintlnS("Grad");
   lcdGotoXY(X_OFFSET_WRITE_SPEED + BUFF_SIZE, Y_COORD_WRITE_SPEED);
   lcdPrintlnS("Grad/s");
}

// ============ Display Ausgabe ============
char angle_buff[BUFF_SIZE];
char old_angle_buff[BUFF_SIZE];
char speed_buff[BUFF_SIZE];
char old_speed_buff[BUFF_SIZE];
int index_write_from_array = 0;

bool switch_output = false;

void write_angle_on_display() {
   if (angle_buff[index_write_from_array] !=
       old_angle_buff[index_write_from_array]) {
      lcdGotoXY(X_OFFSET_WRITE_ANGLE + index_write_from_array,
                Y_COORD_WRITE_ANGLE);
      lcdPrintlnS(&angle_buff[index_write_from_array]);
   }
   index_write_from_array++;
   if (index_write_from_array == MAX_INDEX) {
      index_write_from_array = 0;
      switch_output = !switch_output;
   }
}

void write_speed_on_display() {
   if (speed_buff[index_write_from_array] !=
       old_speed_buff[index_write_from_array]) {
      lcdGotoXY(X_OFFSET_WRITE_SPEED + index_write_from_array,
                Y_COORD_WRITE_SPEED);
      lcdPrintlnS(&speed_buff[index_write_from_array]);
   }
   index_write_from_array++;
   if (index_write_from_array == MAX_INDEX) {
      index_write_from_array = 0;
      switch_output = !switch_output;
   }
}

void display_update() {
   if (!switch_output) {
      write_angle_on_display();
   } else {
      write_speed_on_display();
   }
}

// ============ INPUT LESEN ============
typedef struct {
   bool reset_pressed;       // Zustand von S6
   uint8_t phase_bits;       // Kodierung: (B << 1) | A
   uint32_t raw_timer_ticks; // Rohwert des 32-Bit-Hardwaretimers
} IoInputs;

IoInputs input;

// Konstanten Hardware IO
#define ODR_MASK_PIN_0 (0x01U << 0) // drehgeber IN0 -> PF0
#define ODR_MASK_PIN_1 (0x01U << 1) // drehgeber IN1 -> PF1
#define ODR_MASK_PIN_5 (0x01U << 5) // error
#define ODR_MASK_PIN_6 (0x01U << 6) // backward | reset button
#define ODR_MASK_PIN_7 (0x01U << 7) // forward
#define ODR_MASK_ALL 0xFF

// Reset (S6 -> PF6)
bool is_reset_button_pressed(void) {
   return ODR_MASK_PIN_6 != (GPIOF->IDR & ODR_MASK_PIN_6);
}

// Zeitstempel
uint32_t read_time() { return getTimeStamp(); }

// Phase (Phase-Bits) (GPIO PF0 & PF1)

uint8_t read_GPIO_drehgeber() {
   uint8_t channel_a = GPIOF->IDR & ODR_MASK_PIN_0;
   uint8_t channel_b = GPIOF->IDR & ODR_MASK_PIN_1;
   uint8_t phase_bits = channel_a << 1 | channel_b >> 1;
   return phase_bits;
}

// READ ALL INPUTS
void read_all_inputs() {
   input.phase_bits = read_GPIO_drehgeber();
   input.raw_timer_ticks = read_time();
   input.reset_pressed = is_reset_button_pressed();
}

// ============ OUTPUT SETZEN ============
// RICHTUNG (D23 -> PE7 = vorwärts, D22 -> PE6 = rückwärts)
void set_GPIO_direction(Direction direction) {
   if (direction == DIRECTION_FORWARD) {
      GPIOE->ODR = ODR_MASK_PIN_7;
   } else if (direction == DIRECTION_BACKWARD) {
      GPIOE->ODR = ODR_MASK_PIN_6;
   } else {
      GPIOE->ODR = 0;
   }
}

// FEHLER (D21 -> PE5)
void set_GPIO_error(bool error) {
   if (error) {
      GPIOE->ODR = GPIOE->ODR | ODR_MASK_PIN_5;
   }
}

// ANZAHL PHASENWECHSEL (D8-D15 (8 LEDs) -> PD0-PD7)
void set_GPIO_number_changes(int phase_changes) {
   GPIOD->ODR = phase_changes & ODR_MASK_ALL;
}

// SET ALL OUTPUTS
void set_all_output(Direction direction, bool error, int phase_changes) {
   set_GPIO_direction(direction);
   set_GPIO_error(error);
   set_GPIO_number_changes(phase_changes);
}

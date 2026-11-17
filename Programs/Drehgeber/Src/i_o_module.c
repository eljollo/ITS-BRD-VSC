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
#include "phase.h"
#include "stm32f429xx.h"
// #include "stm32f4xx.h"
// #include "stm32f4xx_hal.h"
#include "timer.h"
#include <stdbool.h>
#include <stdint.h>
// #include <stdio.h>

char angle_buff[BUFF_SIZE];
char speed_buff[BUFF_SIZE];

static char old_angle_buff[BUFF_SIZE];
static char old_speed_buff[BUFF_SIZE];
static int index_write_from_array = 0;

static bool switch_output = false;

// ============ Display init ============
void init_display_output() {
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

void write_angle_on_display() {
   if (angle_buff[index_write_from_array] !=
       old_angle_buff[index_write_from_array]) {
      lcdGotoXY(X_OFFSET_WRITE_ANGLE + index_write_from_array,
                Y_COORD_WRITE_ANGLE);
      lcdPrintC(angle_buff[index_write_from_array]);
      old_angle_buff[index_write_from_array] =
          angle_buff[index_write_from_array];
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
      lcdPrintC(speed_buff[index_write_from_array]);
      old_speed_buff[index_write_from_array] =
          speed_buff[index_write_from_array];
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
// Read all Input Pins
uint8_t read_gpiof_pins() { return GPIOF->IDR; }

// Reset (S6 -> PF6)
bool is_reset_button_pressed(uint8_t gpiof) {
   return ODR_MASK_PIN_6 != (gpiof & ODR_MASK_PIN_6);
}

// Zeitstempel
uint32_t read_time() { return getTimeStamp(); }

// Phase (Phase-Bits) (GPIO PF0 & PF1)
uint8_t read_phase(uint8_t gpiof) {
   uint8_t channel_a = gpiof & ODR_MASK_PIN_0;
   uint8_t channel_b = gpiof & ODR_MASK_PIN_1;
   uint8_t phase_bits = channel_a << 1 | channel_b >> 1;
   return phase_bits;
}

// READ ALL INPUTS
void read_all_inputs(IoInputs *input) {
   uint8_t gpiof_input = read_gpiof_pins();
   input->raw_timer_ticks = read_time();
   input->phase_bits = read_phase(gpiof_input);
   input->reset_pressed = is_reset_button_pressed(gpiof_input);
}

// ============ OUTPUT SETZEN ============
// RESET ALL LEDs
void reset_all_leds() {
   GPIOE->ODR = 0;
   GPIOD->ODR = 0;
}

// RICHTUNG (D23 -> PE7 = vorwärts, D22 -> PE6 = rückwärts)
void set_gpioe_direction(Direction direction) {
   if (direction == DIRECTION_FORWARD) {
      GPIOE->ODR = ODR_MASK_PIN_7;
   } else if (direction == DIRECTION_BACKWARD) {
      GPIOE->ODR = ODR_MASK_PIN_6;
   }
}

// FEHLER (D21 -> PE5)
void set_gpioe_error(bool error) {
   if (error) {
      GPIOE->ODR = GPIOE->ODR | ODR_MASK_PIN_5;
   }
}

// ANZAHL PHASENWECHSEL (D8-D15 (8 LEDs) -> PD0-PD7)
void set_gpio_number_changes(uint64_t phase_changes) {
   GPIOD->ODR = phase_changes & ODR_MASK_ALL;
}

// SET ALL OUTPUTS
void set_all_output(Direction direction, bool error, uint64_t phase_changes) {
   set_gpioe_direction(direction);
   set_gpioe_error(error);
   set_gpio_number_changes(phase_changes);
}

/**
 ******************************************************************************
 * @file    input_module.c
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief   enthält Definitionen, bzw. Implementierungen der in i_o_module.h
 * deklarierten Funktionen
 ******************************************************************************
 */

// ============ INLCUDES ============
#include "input_module.h"
// #include "lcd.h"
#include "bit_masken.h"
// #include "phase.h"
#include "stm32f429xx.h"
// #include "stm32f4xx_hal.h"
#include "timer.h"
#include "timer_hm.h"
#include <stdbool.h>
#include <stdint.h>
// #include <stdio.h>

// ============ INPUT LESEN ============
// Read all Input Pins
uint8_t read_gpiof_pins() { return GPIOF->IDR; }

// Reset (S6 -> PF6)
bool is_reset_button_pressed(uint8_t gpiof) {
   return MASK_PIN_6 != (gpiof & MASK_PIN_6);
}

// Zeitstempel
uint32_t read_time() { return getTimeStamp(); }

// Phase (Phase-Bits) (GPIO PF0 & PF1)
uint8_t read_phase(uint8_t gpiof) {
   uint8_t channel_a = gpiof & MASK_PIN_0;
   uint8_t channel_b = gpiof & MASK_PIN_1;
   uint8_t phase_bits = channel_a << 1 | channel_b >> 1;
   return phase_bits;
}

// READ ALL INPUTS
void read_all_inputs(IoInputs *input) {
   uint8_t gpiof_input = read_gpiof_pins();
   input->timer_ticks = timer_extend(read_time());
   input->phase_bits = read_phase(gpiof_input);
   input->reset_pressed = is_reset_button_pressed(gpiof_input);
}

/**
 ******************************************************************************
 * @file    led_output.c
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief   enthält Definitionen, bzw. Implementierungen der in led_output.h
 * deklarierten Funktionen
 ******************************************************************************
 */

// ============ INLCUDES ============
#include "bit_masken.h"
#include "phase.h"
#include "stm32f429xx.h"

// ============ OUTPUT SETZEN ============
// RESET ALL LEDs
void reset_all_leds() {
   GPIOE->BSRR = MASK_ALL << BSRR_DELETE_AREA;
   GPIOD->BSRR = MASK_ALL << BSRR_DELETE_AREA;
}

// RICHTUNG (D23 -> PE7 = vorwärts, D22 -> PE6 = rückwärts)
static void set_gpioe_direction(Direction direction) {
   if (direction == DIRECTION_FORWARD) {
      GPIOE->BSRR = MASK_PIN_7;
      GPIOE->BSRR = MASK_PIN_6 << BSRR_DELETE_AREA;
   } else if (direction == DIRECTION_BACKWARD) {
      GPIOE->BSRR = MASK_PIN_6;
      GPIOE->BSRR = MASK_PIN_7 << BSRR_DELETE_AREA;
   }
}

// FEHLER (D21 -> PE5)
void set_gpioe_error(bool error) {
   if (error) {
      GPIOE->BSRR = MASK_PIN_5;
   }
}

// ANZAHL PHASENWECHSEL (D8-D15 (8 LEDs) -> PD0-PD7)
void set_gpio_number_changes(int64_t phase_changes) {
   GPIOD->ODR = phase_changes & MASK_ALL;
}

// SET ALL OUTPUTS
void set_all_output(Direction direction, bool error, int64_t phase_changes) {
   set_gpioe_direction(direction);
   set_gpioe_error(error);
   set_gpio_number_changes(phase_changes);
}

// SET PIN FOR OSZILLOSKOP (D16 -> PE0)
void set_pin_for_oszilloskop() {
   GPIOE->ODR ^= MASK_PIN_0;
   //    HAL_Delay(1000);
}

void reset_pin_for_oszilloskop() {
   GPIOE->BSRR = MASK_PIN_0 << BSRR_DELETE_AREA;
   //    HAL_Delay(1000);
}
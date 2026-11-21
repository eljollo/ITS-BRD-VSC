/**
 * @file input_module.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief liest Input angeschlossener Geräte, die ans ITS-Board und Zeit aus dem
 * timer Modul.
 */

#ifndef INPUT_MODULE_H
#define INPUT_MODULE_H

#include <stdbool.h>
#include <stdint.h>

// ============ KONSTANTEN ============
// struct für input
typedef struct {
   bool reset_pressed;   // Zustand von S6
   uint8_t phase_bits;   // Kodierung: (A << 1) | B
   uint64_t timer_ticks; // auf 64 Bit erweiterter Wert des timers
} IoInputs;

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   liest alle relevanten Eingänge und speichert sie in IoInputs struct.
 ******************************************************************************
 */
void read_all_inputs(IoInputs *input);

#endif
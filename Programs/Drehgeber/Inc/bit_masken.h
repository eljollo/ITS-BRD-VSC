/**
 * @file bit_masken.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief Bit-Masken für Bitoperationen bzgl. LEDs oder anderen Bitoperationen
 * die benötigt werden.
 */

#ifndef BIT_MASKEN_H
#define BIT_MASKEN_H

// für Hardware IO Bitoperationen
#define MASK_PIN_0 (0x01U << 0) // drehgeber IN0 -> PF0
#define MASK_PIN_1 (0x01U << 1) // drehgeber IN1 -> PF1
#define MASK_PIN_5 (0x01U << 5) // error
#define MASK_PIN_6 (0x01U << 6) // backward | reset button
#define MASK_PIN_7 (0x01U << 7) // forward
#define MASK_ALL 0xFF
#define BSRR_DELETE_AREA 16

#endif
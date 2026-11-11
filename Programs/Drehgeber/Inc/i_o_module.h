/**
 * @file i_o_module.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief .
 */

#ifndef IO_H
#define IO_H

#include "structs.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t phase_bits;       // Kodierung: (B << 1) | A
    uint32_t raw_timer_ticks; // Rohwert des 32-Bit-Hardwaretimers
    bool reset_pressed;       // Zustand von S6
} IoInputs;

// WICHTIG!!! I/O MODUL
// Hardware initialisieren, einschließlich GPIO und 90-MHz-Timer.
void io_init(void);

// WICHTIG!!! I/O MODUL
// Am Anfang der Super-Loop Phase, nahen Timerwert und S6 einlesen.
// Während der späteren Verarbeitung nicht nochmals nachlesen.
IoInputs io_read_inputs(void);

// WICHTIG!!! I/O MODUL
// Niederwertigste acht Bits des richtungsabhängigen Zählers auf D8–D15.
void io_write_count_leds(uint8_t low_eight_bits);

// WICHTIG!!! I/O MODUL
// LEDs D22/D23 entsprechend der zuletzt erkannten Richtung setzen.
void io_write_direction_leds(Direction direction);

// WICHTIG!!! I/O MODUL
// Fehler-LED D21 setzen beziehungsweise löschen.
void io_write_error_led(bool on);

// WICHTIG!!! I/O MODUL
// LED-Ausgänge beim Programm-Reset in den Anfangszustand bringen.
void io_reset_outputs(void);

// WICHTIG!!! I/O MODUL
// LCD einmalig initialisieren; feste Texte einmalig schreiben.
// Annahme dieses Entwurfs: zwei Zeilen mit je 16 Stellen.
// Spalten 0–6 enthalten feste Beschriftungen,
// Spalten 7–15 sind für wechselnde Werte reserviert.
void io_display_init_layout(void);

// WICHTIG!!! I/O MODUL
// Genau EIN Zeichen an eine LCD-Position schreiben.
void io_display_write_char_at(uint8_t row, uint8_t column, char character);

#endif
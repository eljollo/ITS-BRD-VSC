/**
 * @file display.c
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief enthält Implementierungen der in display.h deklarierten Funktionen.
 */

 #include "display.h"
#include "i_o_module.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

enum {
    VALUE_WIDTH = 9,
    VALUE_START_COLUMN = 7,
    VALUE_COUNT = 2 * VALUE_WIDTH,
};

static char angle_text[VALUE_WIDTH + 1];
static char speed_text[VALUE_WIDTH + 1];
static uint8_t next_character;
static bool pending;

static void format_value(char target[VALUE_WIDTH + 1], double value)
{
    char temporary[48];
    int written = snprintf(temporary, sizeof temporary, "%9.1f", value);

    if (written < 0 || written > VALUE_WIDTH) {
        memcpy(target, "#########", VALUE_WIDTH + 1);
        return;
    }

    memcpy(target, temporary, VALUE_WIDTH);
    target[VALUE_WIDTH] = '\0';
}

void display_init(void)
{
    display_reset_pending();

    // WICHTIG!!! I/O MODUL
    // Feste Beschriftungen nur EINMAL beim Programmstart schreiben.
    io_display_init_layout();
}

void display_reset_pending(void)
{
    next_character = 0;
    pending = false;
}

void display_queue_values(double angle, bool speed_valid, double speed)
{
    format_value(angle_text, angle);

    if (speed_valid) {
        format_value(speed_text, speed);
    } else {
        memcpy(speed_text, "       --", VALUE_WIDTH + 1);
    }

    // Eine neuere Wertausgabe ersetzt gegebenenfalls die noch nicht
    // vollständig geschriebene alte Wertausgabe.
    next_character = 0;
    pending = true;
}

void display_step(void)
{
    if (!pending) {
        return;
    }

    uint8_t row = (next_character < VALUE_WIDTH) ? 0U : 1U;
    uint8_t index_in_value =
        (uint8_t)(next_character % VALUE_WIDTH);
    char character =
        (row == 0U) ? angle_text[index_in_value]
                    : speed_text[index_in_value];

    // WICHTIG!!! I/O MODUL
    // Genau EIN Zeichen dieses Schleifendurchlaufs schreiben.
    io_display_write_char_at(
        row,
        (uint8_t)(VALUE_START_COLUMN + index_in_value),
        character
    );

    next_character++;
    if (next_character >= VALUE_COUNT) {
        pending = false;
    }
}
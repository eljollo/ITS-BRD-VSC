/**
 * @file timer.c
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief enthält Implementierungen der in timer.h deklarierten Funktionen.
 */

#include "timer.h"

#include <stdbool.h>
#include <stdint.h>

static bool has_previous_raw;
static uint32_t previous_raw;
static uint64_t extended_ticks;

void timer_reset_extension(void)
{
    has_previous_raw = false;
    previous_raw = 0;
    extended_ticks = 0;
}

uint64_t timer_extend(uint32_t raw_ticks)
{
    if (!has_previous_raw) {
        previous_raw = raw_ticks;
        extended_ticks = raw_ticks;
        has_previous_raw = true;
        return extended_ticks;
    }

    // Vorzeichenlose 32-Bit-Subtraktion behandelt einen Überlauf
    // zwischen ZWEI unmittelbar aufeinanderfolgenden Abfragen.
    uint32_t elapsed_raw_ticks = raw_ticks - previous_raw;

    extended_ticks += elapsed_raw_ticks;
    previous_raw = raw_ticks;

    return extended_ticks;
}
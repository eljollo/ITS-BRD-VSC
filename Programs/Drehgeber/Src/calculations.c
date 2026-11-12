/**
 * @file calculations.c
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief enthält Implementierungen der in calculations.h deklarierten Funktionen.
 */

// Zeitberechnung (timestamp differenz)
// Zugriff auf Phase C-Struct um Zeiten zu bekommen


// 300 Schlitze/Umdrehung * 4 Phasen/Schlitz = 1200 Phasen/Umdrehung


// Check zeitstamps auf 300 ms
// Berechnung Winkel 
// Berechnung Winkelgeschwindigkeit

// struct für älteren Zählerstand
// berechnung.c
#include "../Inc/calculations.h"
#include "../Inc/structs.h"
#include <stdbool.h>

// 1200 phasenwechsel entsprechen einmal 360 grad
static const double DEGREES_PER_CHANGE = 360.0 / 1200.0;

// 90 timer-ticks pro mikrosekunde
static const double TICKS_PER_SECOND = 90000000.0;

double calculate_angle(int64_t phase_count) {
    return (double)phase_count * DEGREES_PER_CHANGE;
}

bool calculate_speed(PhaseCountSnapshot start, PhaseCountSnapshot end, double *speed_degrees_per_second) {
    if (speed_degrees_per_second == 0 ||
        !start.has_last_change ||
        !end.has_last_change ||
        end.change_ticks <= start.change_ticks ||
        end.change_number <= start.change_number) {
        return false;
    }

    double count_difference = (double)end.count - (double)start.count;
    double tick_difference = (double)(end.change_ticks - start.change_ticks);

    *speed_degrees_per_second = count_difference * DEGREES_PER_CHANGE * TICKS_PER_SECOND / tick_difference;

    return true;
}
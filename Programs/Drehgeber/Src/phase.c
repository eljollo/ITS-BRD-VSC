/**
 * @file phase.c
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief enthält Implementierungen der in phase.h deklarierten Funktionen.
 */

// Phasenübergang & Phasenzähler
// Zugriff auf Phase C-Struct um Phase bzw deren veränderung zu checken

// Fehlerfall, Drehrichtung (L, R, unbekannt) und aktuelle Phase in statischen
// Variablen des entsprechenden Moduls Weitere Variable speichert Anzahl der
// Phasenwechsel

// START
// aktuelle Phase
// zwei Zählerstände mit Zeitstempel

// (prev)   a   b   c   d (current)
// a        0  +1   E  -1
// b       -1   0  +1   E
// c        E  -1   0  +1
// d       +1   E  -1   0

// +1 vorwärts
// -1 rückwärts
// 0 keine Veränderung (Drehrichtung bleibt bestehen)
// E fehlermeldung

// Letzte Phase                         – für den Vergleich mit der neuen Phase.
// Phasenzähler                         – zählt gültige Schritte mit Vorzeichen.
// Zuletzt erkannte Drehrichtung        – für die Richtungs-LEDs; „keine
// Änderung“ soll nicht automatisch die letzte Richtung löschen. Fehlerzustand
// – damit ein erkannter Fehler bis zum Reset erhalten bleibt. Zeitstempel zum
// Zählerstand          – wann der letzte gezählte Wechsel beobachtet wurde; das
// braucht deine Geschwindigkeitsberechnung. Kennzeichen für den ersten Messwert
// – beim Start gibt es noch keine „letzte Phase“, mit der man vergleichen
// könnte

#include "phase.h"
#include <stdbool.h>
#include <stdint.h>

// Konstanten
#define ERROR_CODE 99

// struct um Zustand festzuhalten
static PhaseState phase_state;

// phase reset
void phase_reset() { phase_state = (PhaseState){0}; }

// phase table (previous phase x current phase)
int phase_table[4][4] = {
    {0, 1, ERROR_CODE, -1},
    {-1, 0, 1, ERROR_CODE},
    {ERROR_CODE, -1, 0, 1},
    {1, ERROR_CODE, -1, 0},
};

// phase_bits zu phase_table index
static int phase_index(uint8_t phase_bits) {
   switch (phase_bits) {
   case 0U:
      return 0; // phase a 00
   case 2U:
      return 1; // phase b 10
   case 3U:
      return 2; // phase c 11
   case 1U:
      return 3; // phase d 01
   default:
      return -1;
   }
}

// Phasenwechsel + Zeitstempel (Phasenwechsel erhält Zeitstempel der aktuellen
// Phase wenn Phasenwechsel stattfindet) Phasenzähler (zählt anzahl
// Phasenwechsel, erhält Zeitstempel )

void phase_process(Phase current) {
   // hätte man vermutlich auch als Pointerübergabe von phase_state direkt
   // machen können
   PhaseState *state = &phase_state;
   if (state->error) {
      return;
   }
   int current_phase = phase_index(
       current.phase_bits); // aktuelle phase ausgehend von phase_bits
   if (current_phase == -1) {
      state->error = true;
      return;
   }
   if (state->has_previous) { // wenn previous existiert
      // vorherige phase ausgehend von phase_bits
      int previous_phase = phase_index(state->previous.phase_bits);
      // phasenwechsel ? (wenn previous und ungleich aktueller phase)
      if (current_phase != previous_phase) {
         int phase_change = phase_table[previous_phase][current_phase];
         // Fehlersituation ? (wurde eine phase übersprungen?)
         if (phase_change != ERROR_CODE) {
            // legit phasenwechsel seit reset boolean
            state->has_last_change = true;
            // timer setzen bei phasenwechsel
            state->last_change_ticks = current.timer_ticks;
            if (phase_change == 1) {
               state->last_direction = DIRECTION_FORWARD;
            }
            if (phase_change == -1) {
               state->last_direction = DIRECTION_BACKWARD;
            }
            state->phase_counter += phase_change; // phasenzähler aktualisieren
            state->change_number++; // wechsel-counter inkrementieren
         } else {
            state->error = true;
            return;
         }
      }
   }
   state->has_previous = true;
   state->previous = current;
}

bool phase_has_error(void) { return phase_state.error; }

Direction phase_get_last_direction(void) { return phase_state.last_direction; }

PhaseCountSnapshot phase_get_counter_sample(void) {
   PhaseCountSnapshot result = {
       .count = phase_state.phase_counter,
       .change_ticks = phase_state.last_change_ticks,
       .change_number = phase_state.change_number,
       .has_last_change = phase_state.has_last_change,
   };

   return result;
}
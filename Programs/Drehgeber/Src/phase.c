// Phasenübergang & Phasenzähler
// Zugriff auf Phase C-Struct um Phase bzw deren veränderung zu checken

// Fehlerfall, Drehrichtung (L, R, unbekannt) und aktuelle Phase in statischen Variablen des entsprechenden Moduls
// Weitere Variable speichert Anzahl der Phasenwechsel

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
// Zuletzt erkannte Drehrichtung        – für die Richtungs-LEDs; „keine Änderung“ soll nicht automatisch die letzte Richtung löschen.
// Fehlerzustand                        – damit ein erkannter Fehler bis zum Reset erhalten bleibt.
// Zeitstempel zum Zählerstand          – wann der letzte gezählte Wechsel beobachtet wurde; das braucht deine Geschwindigkeitsberechnung.
// Kennzeichen für den ersten Messwert  – beim Start gibt es noch keine „letzte Phase“, mit der man vergleichen könnte


#include <stdbool.h>
#include <stdint.h>
#include "../Inc/i_o_module.h"
#include "../Inc/phase.h"

// Konstanten
#define ERROR 99

// struct als datentyp für inhalt / informationen der Phase
typedef struct {
    uint8_t phase_bits;
    uint32_t timer_ticks;
} Phase;


// enum für direction
typedef enum {
    DIRECTION_UNKNOWN,
    DIRECTION_FORWARD,
    DIRECTION_BACKWARD
} Direction ;


// struct als datentyp für Zustand der Phase
typedef struct {
    Phase previous;
    bool has_previous;

    int32_t phase_counter;
    
    uint32_t last_change_ticks; // für phasenwechsel und phasenzähler gleich
    bool has_last_change;       // gab es seit reset einen gültigen phassenwechsel

    Direction last_direction;
    bool error;
} PhaseState;


// Variable um Zustand festzuhalten
static PhaseState state;


// phase reset
void phase_reset(){ 
    state.has_previous = false;
    state.phase_counter = 0 ;
    state.has_last_change = false;
    state.last_direction = DIRECTION_UNKNOWN;
    state.error = false;
}


// phase table (previous phase x current phase)
int phase_table[4][4] = {   {0, 1, ERROR, -1},
                            {-1, 0, 1, ERROR},
                            {ERROR, -1, 0, 1},
                            {1, ERROR, -1, 0}
                        };

// phase_bits zu phase_table index
static int phase_index(uint8_t phase_bits){
    switch (phase_bits) {
        case 0U: return 0;  // phase a
        case 2U: return 1;  // phase b
        case 3U: return 2;  // phase c
        case 1U: return 3;  // phase d
        default: return -1;
    }
}

// Phasenwechsel + Zeitstempel (Phasenwechsel erhält Zeitstempel der aktuellen Phase wenn Phasenwechsel stattfindet)
// Phasenzähler (zählt anzahl Phasenwechsel, erhält Zeitstempel )

void phase_process(Phase current){
    if (state.error) {
        return;
    }
    int current_phase = phase_index(current.phase_bits);                // aktuelle phase ausgehend von phase_bits
    if (current_phase==-1) {
        state.error = true;
        return;
    }
    if (state.has_previous) {                                           // wenn previous existiert
        int previous_phase = phase_index(state.previous.phase_bits);    // vorherige phase ausgehend von phase_bits
        if (current_phase!=previous_phase) {                            // phasenwechsel ? (wenn previous und ungleich aktueller phase)
            int phase_change = phase_table[previous_phase][current_phase];
            if (phase_change!=ERROR) {                                  // Fehlersituation ? (wurde eine phase übersprungen?)
                state.has_last_change = true;                           // legit phasenwechsel seit reset boolean
                state.last_change_ticks = current.timer_ticks;          // timer setzen bei phasenwechsel
                if (phase_change == 1) {
                    state.last_direction = DIRECTION_FORWARD;           // Drehrichtung
                }
                if (phase_change == -1) {
                    state.last_direction = DIRECTION_BACKWARD;          // Drehrichtung
                }
                state.phase_counter += phase_change;                     // phasenzähler aktualisieren
            } else {
                state.error = true;
                return;
            }
        }
    }
    state.has_previous = true;
    state.previous = current;
}



// timestamp aufnehmen

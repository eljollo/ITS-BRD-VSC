#include "../Inc/i_o_module.h"
#include "../Inc/phase.h"
#include <stdint.h>

uint32_t pins = read_gpiof_inputs(); // Platzhalter: tatsächlichen Zugriff in eurer Board-Bibliothek nachsehen

uint8_t a = (pins >> 0) & 1u;          // Bit von PF0
uint8_t b = (pins >> 1) & 1u;          // Bit von PF1
uint8_t phase_bits = (a << 1) | b;     // beide Eingangswerte zusammenfassen

// bits von pins werden gezogen / gelesen und a auf bit 1, b auf bit 0 gesetzt /wichtig für Tabellenindizes und 

// I/O liest Phase mit Zeitstempel und gibt sie an phase weiter
Phase io_read_phase_sample() // setzt die phase bits in ein "Phase current"


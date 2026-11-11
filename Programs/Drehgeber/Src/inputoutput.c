#include <stdbool.h>
#include "lcd.h"
#include "../Inc/inputoutput.h"
/**
  ******************************************************************************
  * @file    inputoutput.c
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   enthält Implementierungen der in inputoutput.h deklarierten Funktionen
  ******************************************************************************
  */

//Display - initialisierungsausgabe:
void initial_display_output(void) {
    lcdPrintlnS("Hallo Welt! ");
}

//Display - winkelausgabe:
void change_winkel_output_1(char number_new) {
    lcdPrintlnS(&number_new); //platzhalter-Anweisung
}

void change_winkel_output_2(char number_new) {
    lcdPrintlnS(&number_new); //platzhalter-Anweisung
}

void change_winkel_output_3(char number_new) {
    lcdPrintlnS(&number_new); //platzhalter-Anweisung
}

void change_winkel_output_n1(char number_new) {
    lcdPrintlnS(&number_new); //platzhalter-Anweisung
}

//Display - winkelgeschwindigkeitsausgabe:
void change_winkegeschwindigkeit_output_1(char number_new) {
    lcdPrintlnS(&number_new); //platzhalter-Anweisung
}

void change_winkegeschwindigkeit_output_2(char number_new) {
    lcdPrintlnS(&number_new); //platzhalter-Anweisung
}

void change_winkegeschwindigkeit_output_3(char number_new) {
    lcdPrintlnS(&number_new); //platzhalter-Anweisung
}

void change_winkegeschwindigkeit_output_n1(char number_new) {
    lcdPrintlnS(&number_new); //platzhalter-Anweisung
}

void change_winkegeschwindigkeit_output_n2(char number_new) {
    lcdPrintlnS(&number_new); //platzhalter-Anweisung
}

void change_winkegeschwindigkeit_output_n3(char number_new) {
    lcdPrintlnS(&number_new); //platzhalter-Anweisung
}

//ReadPINs-Functions:
const int BIT_COMP = 1234; // wird noch auf passenden Wert für Bit-Vergleich gesetzt
bool s6_is_pressed = false;
bool reads_button_s6_for_reset() {
    s6_is_pressed = true; //bitweiser vergleich mit BIT_COMP
    return s6_is_pressed;
}

int read_gpio_pin0_to_pin7() {return 1;}

//LED-Output-Functions:
void write_phase_number_to_led() {}

void last_turn_forward() {}
void last_turn_backward() {}
void show_error() {}
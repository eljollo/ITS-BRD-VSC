#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"
#include "stm32f4xx_hal.h"
#include "../Inc/inputoutput.h"
/**
  ******************************************************************************
  * @file    inputoutput.c
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   enthält Definitionen, bzw. Implementierungen der in inputoutput.h deklarierten Funktionen
  ******************************************************************************
  */

//Display - initialisierungsausgabe:
void initial_display_output(void) {
    lcdGotoXY(1, 3);
    lcdPrintlnS("Winkel: ");
    lcdGotoXY(1, 10);
    lcdPrintlnS("Geschwindigkeit: ");
    lcdGotoXY(13, 3);
    lcdPrintC(',');
    lcdGotoXY(35, 3);
    lcdPrintlnS("Grad");
    lcdGotoXY(25, 10);
    lcdPrintC(',');
    lcdGotoXY(35, 10);
    lcdPrintlnS("Grad/s");
}

//Display - winkelausgabe:
void change_winkel_output_1(char number_new) {
    lcdGotoXY(12, 3);
    lcdPrintC(number_new); 
}

void change_winkel_output_2(char number_new) {
    lcdGotoXY(11, 3);
    lcdPrintC(number_new);
}

void change_winkel_output_3(char number_new) {
    lcdGotoXY(10, 3);
    lcdPrintC(number_new);
}

void change_winkel_output_4(char number_new) {
    lcdGotoXY(9, 3);
    lcdPrintC(number_new);
}

void change_winkel_output_n1(char number_new) {
    lcdGotoXY(14, 3);
    lcdPrintC(number_new);
}

//Display - winkelgeschwindigkeitsausgabe:
void change_winkegeschwindigkeit_output_1(char number_new) {
    lcdGotoXY(24, 10);
    lcdPrintC(number_new);
}

void change_winkegeschwindigkeit_output_2(char number_new) {
    lcdGotoXY(23, 10);
    lcdPrintC(number_new);
}

void change_winkegeschwindigkeit_output_3(char number_new) {
    lcdGotoXY(22, 10);
    lcdPrintC(number_new);
}

void change_winkegeschwindigkeit_output_4(char number_new) {
    lcdGotoXY(21, 10);
    lcdPrintC(number_new);
}

void change_winkegeschwindigkeit_output_n1(char number_new) {
    lcdGotoXY(26, 10);
    lcdPrintC(number_new);
}

void change_winkegeschwindigkeit_output_n2(char number_new) {
    lcdGotoXY(27, 10);
    lcdPrintC(number_new);
}

void change_winkegeschwindigkeit_output_n3(char number_new) {
    lcdGotoXY(28, 10);
    lcdPrintC(number_new);
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
void write_phase_number_to_led(int param) {}

void last_turn_forward() {}
void last_turn_backward() {}
void show_error() {}
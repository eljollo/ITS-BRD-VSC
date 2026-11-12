#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"
#include "stm32f429xx.h"
#include "timer.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
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

//init GPIOs:
void init_gpio() {
    //GPIOD: PD0 bis PD7 als Output (01) konfigurieren, restliche als Output
    GPIOF->MODER &= ~0x0000FFFFU; //need to replace with matching constants
    GPIOD->MODER |=  0x00005555U;

    //GPIOE: PE1 bis PE7 als Output (01) konfigurieren (PE0 bleibt unberührt)
    GPIOF->MODER &= ~0x0000FFFCU;
    GPIOE->MODER |=  0x00005554U;

    //GPIOF: PF0 und PF1 als Input (00) konfigurieren
    GPIOF->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1);

    //setzt alle Bits auf 0: (Input- und Output-Bereiche)
    led_reset();
    GPIOF->ODR = 0;
}

//ReadPINs-Functions:

const int BIT_COMP = 1234; // wird noch auf passenden Wert für Bit-Vergleich gesetzt //unint32-wert nötig
bool s6_is_pressed = false;
bool reads_button_s6_for_reset() {
    s6_is_pressed = true;
    s6_is_pressed = BIT_COMP & GPIOF->IDR; //bitweiser vergleich mit BIT_COMP
    return s6_is_pressed;
}

uint32_t read_gpio_pin0_to_pin7() {
    return GPIOF->IDR;
} //called in read_input()

//init struct for input:
IoInputs inputs;

IoInputs read_input() {
    inputs.reset_pressed = reads_button_s6_for_reset();
    inputs.phase_bits = read_gpio_pin0_to_pin7(); //niedrigwertigste letzte 2 bits per bit-Operation
    inputs.raw_timer_ticks = 12;//platzhalter, hier wird read_timer() aufgerufen //liest timer-Register aus
}

//LED-Output-Functions:
void write_phase_number_to_led(uint8_t latest_count) {
    GPIOE->ODR = latest_count;
}

void last_turn_forward() {
    GPIOD->ODR = 123; //platzhalter
}
void last_turn_backward() {
    GPIOD->ODR = 123; //platzhalter
}
void show_error() {
    GPIOD->ODR = 123; //platzhalter
}

void led_reset() {
    GPIOD->ODR = 0;
    GPIOE->ODR = 0;
}

//timer-IO-functions:
uint32_t read_timer() {
    return getTimeStamp(); //platzhalter, wie CNT->IDR?
}

void timer_reset() {
    TIM2->CNT = 0;
}
#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"
#include "stm32f429xx.h"
#include "timer.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "../Inc/inputoutput.h"

#define BIT_COMP (1U << 6)

/**
  ******************************************************************************
  * @file    inputoutput.c
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   enthält Definitionen, bzw. Implementierungen der in inputoutput.h deklarierten Funktionen
  ******************************************************************************
  */
//declare cursor-constants

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
//define config-constants:

//ReadPINs-Functions:
bool s6_is_pressed = false;
bool reads_button_s6_for_reset() {
    s6_is_pressed = (GPIOF->IDR & BIT_COMP) != 0U; //bitweiser vergleich mit BIT_COMP
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
    inputs.raw_timer_ticks = read_timer();//platzhalter, hier wird read_timer() aufgerufen //liest timer-Register aus
    return inputs;
}

//LED-Output-Functions:
void write_phase_number_to_led(uint8_t latest_count) {
    GPIOD->ODR = latest_count;
}

void last_turn_forward() {
    GPIOE->BSRR = LED23_FORWARD; //platzhalter d23 anpassen an bsrr jew.
}
void last_turn_backward() {
    GPIOE->BSRR = LED22_BACKWARD; //platzhalter d22
}
void show_error() {
    GPIOE->BSRR = LED21_ERROR;
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
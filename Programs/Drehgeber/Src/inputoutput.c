#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "lcd.h"
#include "stm32f429xx.h"
#include "timer.h"
#include "../Inc/inputoutput.h"

#define BIT_COMP (1U << 7U) //U: unsigned int

/**
  ******************************************************************************
  * @file    inputoutput.c
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   enthält Definitionen, bzw. Implementierungen der in inputoutput.h deklarierten Funktionen
  ******************************************************************************
  */
//declare cursor-constants
//Display - initialisierungsausgabe:
#define X1 1
#define X2 13
#define X3 25
#define X4 35
#define Y1 3
#define Y2 10
void initial_display_output(void) {
    lcdGotoXY(X1, 3);
    lcdPrintlnS("Winkel: ");
    lcdGotoXY(X1, Y2);
    lcdPrintlnS("Geschwindigkeit: ");
    lcdGotoXY(X2, Y1);
    lcdPrintC(',');
    lcdGotoXY(X4, Y1);
    lcdPrintlnS("Grad");
    lcdGotoXY(X3, Y2);
    lcdPrintC(',');
    lcdGotoXY(X4, Y2);
    lcdPrintlnS("Grad/s");
}

//update_display_functions:(docs, siehe inputoutput.h)

void update_winkel(double current_winkel) {
    static char old_winkel_buffer[BUFFER_SIZE] = {0}; //static preserves content between function-calls.
    char current_winkel_buffer[BUFFER_SIZE];
    snprintf(current_winkel_buffer, sizeof(current_winkel_buffer), "%8.1f", current_winkel);
    for (int index = 0; index<=MAX_INDEX; index++) {
        if (current_winkel_buffer[index] == '\0' &&
            old_winkel_buffer[index] == '\0') {
            break;
        }
        if (current_winkel_buffer[index] != old_winkel_buffer[index]) {
            lcdGotoXY(OFFSET_WINKEL_X + index, OFFSET_WINKEL_Y);
            lcdPrintC(current_winkel_buffer[index]);
            old_winkel_buffer[index] = current_winkel_buffer[index];
            break;
        }
    }
}

void update_speed(double current_speed) {
    static char old_speed_buffer[BUFFER_SIZE] = {0};
    char current_speed_buffer[BUFFER_SIZE];
    snprintf(current_speed_buffer, sizeof(current_speed_buffer), "%8.1f", current_speed);
    for (int index =0; index<=MAX_INDEX; index++) {
        if (current_speed_buffer[index] == '\0' &&
            old_speed_buffer[index] == '\0') {
            break;
        }
        if (current_speed_buffer[index] != old_speed_buffer[index]) {
            lcdGotoXY(OFFSET_SPEED_X + index, OFFSET_SPEED_Y);
            lcdPrintC(current_speed_buffer[index]);
            old_speed_buffer[index] = current_speed_buffer[index];
            break;
        }
    }
}

//in case. delete if not being called from main in final version
/*
void update_display(double winkel, double geschwindigkeit) {
    update_winkel(winkel);
    update_speed(geschwindigkeit);
}
*/
//init GPIOs:
//define config-constants:
void init_gpio() {
    GPIOD->ODR = 0x0; //constants beim testen anpassen
    GPIOE->BSRR = 0xFFFF0000U;
    GPIOD->BSRR = 0xFFFF0000U;
    //GPIOF wird nicht auf 0 gesetzt, da von gedrückten Buttons abh.(Race Conditions vermeiden u.a.)
}

//ReadPINs-Functions:
bool s6_is_pressed = false;
bool reads_button_s6_for_reset() {
    s6_is_pressed = (GPIOF->IDR & BIT_COMP) != 0U;
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
#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "timer.h"
/**
  ******************************************************************************
  * @file    inputoutput.h 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   Modul enthält Funktionen für benötigte Input-Operationen, sowie Output via LED und LcdDisplay.
  *          Details stehen ggf. in den Kommentaren der jew. Deklarationen 
  ******************************************************************************
  */

/*
Display-Functions:
*/
/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @param   void
  * @brief   wird beim Programmstart oder bei Re-Initialisierung aufgerufen. sorgt für erste Ausgabe auf Display,
  *          d.h. schreibt "Winkel: " und "Winkelgeschwindigkeit: " auf Display. 
  ******************************************************************************
  */
extern void initial_display_output(void);

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @param   char number_new
  * @brief   setzen übergebenes char an übergebener Stelle von Winkelausgabe(1=einer; 2=zehner; 3=hunderter; 4=tausender; n1=zehntel), d.h.
  *          LCDGoTo(x, y) wird entsprechend vor Ausgabe gesetzt.(Anm.: 360/1200=0,3 grad entspricht 1 Phasenverschiebung ,daher nur 1 Nachkommastelle n1)
  *          Werden von main aufgerufen, je nach Bedarf
  ******************************************************************************
  */
extern void change_winkel_output_1(char number_new);
extern void change_winkel_output_2(char number_new);
extern void change_winkel_output_3(char number_new);
extern void change_winkel_output_4(char number_new);
extern void change_winkel_output_n1(char number_new);

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @param   char number_new
  * @brief   setzen übergebenes char an entsprechender Stelle von Winkelgeschwindigkeits-Ausgabe(1=einer; 2=zehner; 3=tausender),
  *          d.h. LCDGoTo(x, y) wird entsprechend gesetzt.
  *          Werden von main aufgerufen, je nach Bedarf
  ******************************************************************************
  */
extern void change_winkegeschwindigkeit_output_1(char number_new);
extern void change_winkegeschwindigkeit_output_2(char number_new);
extern void change_winkegeschwindigkeit_output_3(char number_new);
extern void change_winkegeschwindigkeit_output_4(char number_new);

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @param   char number_new
  * @brief   ändern zeichen an entsprechender  Nachkomma-Stelle von Winkelausgabe(n1=zehntel; n2=hundertstel; n3=tausendstel),
  *          d.h. LCDGoTo(x, y) wird entsprechend gesetzt.
  *          Werden von main aufgerufen, je nach Bedarf
  ******************************************************************************
  */
extern void change_winkegeschwindigkeit_output_n1(char number_new);
extern void change_winkegeschwindigkeit_output_n2(char number_new);
extern void change_winkegeschwindigkeit_output_n3(char number_new);

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @param   void
  * @brief   initialisiert GPIOs, d.h. setzt alle Bits auf 0
  ******************************************************************************
  */
  extern void init_gpio();


/*ReadPINs-Functions:*/
/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @param   
  * @brief   liest Adressbereich der Buttons S0-S8 aus, und macht bitweisen Vergleich mit BIT_COMP, um zu prüfen,
  *          ob S6 gedrückt wurde. Falls gedrückt, wird S6_IS_PRESSED auf true gesetzt.
  ******************************************************************************
  */
extern const int BIT_COMP; // wird in inputoutput.c auf passenden Wert für Vergleich gesetzt
extern bool s6_is_pressed;
extern bool reads_button_s6_for_reset();

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @param   
  * @brief   liest Adressbereich der GPIOs PF0-PF7 (Pins IN0-IN7) aus und gibt den aktuellen Zustand als Integer zurück
  *          (für Zustandsermittlung in phase/main, d.h. welche Phase aktuell?).
  ******************************************************************************
  */
extern uint32_t read_gpio_pin0_to_pin7();

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @param   
  * @brief  liest Werte der GPIOs ein, sowie des timer-Registers und schreibt diese an die entsprechenden Variablen in IoInputs
  *         nutzt ggf. restliche read-input-functions
  ******************************************************************************
*/
typedef struct {
    uint8_t phase_bits;       // Kodierung: (B << 1) | A
    uint32_t raw_timer_ticks; // Rohwert des 32-Bit-Hardwaretimers
    bool reset_pressed;       // Zustand von S6
} IoInputs;

IoInputs extern read_input();

/*LED-Output-Functions:*/

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   Setzt in Register/Adressen, die LEDs steuern alle Bits auf 0
  ******************************************************************************
  */
  //define constant 0x0000...
extern void led_reset();

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   Nimmt einen int-Wert an und schreibt die niedrigwertigsten 8 Bit
  *          in den Adressbereich, der die LED-Ausgabe von D8-D15(GPIOs PD0 bis PD7) steuert.
  ******************************************************************************
  */
extern void write_phase_number_to_led(uint8_t latest_count);

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @param   
  * @brief   last_turn_forward() schaltet LED D23 an, last_turn_backward() LED22,
  *          show_error schaltet LED21 an
  ******************************************************************************
  */
extern void last_turn_forward();
extern void last_turn_backward();
extern void show_error();

/*timer-IO-Functions */
/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @param   
  * @brief   liest aktuellen Wert vom CNT-Register aus und 
  ******************************************************************************
  */
  extern uint32_t read_timer();

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @param   
  * @brief   setzt alle Bits im Timer-Register(CNT) auf 0
  ******************************************************************************
  */  
  extern void timer_reset();
#include <stdbool.h>
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
  * @brief   wird beim Programmstart oder bei Re-Initialisierung aufgerufen. sorgt für erste Ausgabe auf Display,
  *          d.h. schreibt "Winkel: " und "Winkelgeschwindigkeit: " auf Display. 
  ******************************************************************************
  */
extern void initial_display_output(void);

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   setzen übergebenes char an übergebener Stelle von Winkelausgabe(1=einer; 2=zehner; 3=tausender; n1=zehntel), d.h.
  *          LCDGoTo(x, y) wird entsprechend vor Ausgabe gesetzt.(Anm.: 360/1200=0,3 grad entspricht 1 Phasenverschiebung ,daher nur 1 Nachkommastelle n1)
  *          Werden von main aufgerufen, je nach Bedarf
  ******************************************************************************
  */
extern void change_winkel_output_1(char number_new);
extern void change_winkel_output_2(char number_new);
extern void change_winkel_output_3(char number_new);
extern void change_winkel_output_n1(char number_new);

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   setzen übergebenes char an entsprechender Stelle von Winkelgeschwindigkeits-Ausgabe(1=einer; 2=zehner; 3=tausender),
  *          d.h. LCDGoTo(x, y) wird entsprechend gesetzt.
  *          Werden von main aufgerufen, je nach Bedarf
  ******************************************************************************
  */
extern void change_winkegeschwindigkeit_output_1(char number_new);
extern void change_winkegeschwindigkeit_output_2(char number_new);
extern void change_winkegeschwindigkeit_output_3(char number_new);

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   ändern zeichen an entsprechender  Nachkomma-Stelle von Winkelausgabe(n1=zehntel; n2=hundertstel; n3=tausendstel),
  *          d.h. LCDGoTo(x, y) wird entsprechend gesetzt.
  *          Werden von main aufgerufen, je nach Bedarf
  ******************************************************************************
  */
extern void change_winkegeschwindigkeit_output_n1(char number_new);
extern void change_winkegeschwindigkeit_output_n2(char number_new);
extern void change_winkegeschwindigkeit_output_n3(char number_new);

/*ReadPINs-Functions:*/
/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
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
  * @brief   liest Adressbereich der GPIOs PF0-PF7 (Pins IN0-IN7) aus und gibt den aktuellen Zustand als Integer zurück
  *          (für Zustandsermittlung in phase/main, d.h. welche Phase aktuell?).
  ******************************************************************************
  */
extern int read_gpio_pin0_to_pin7();

/*LED-Output-Functions:*/

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   Nimmt einen int-Wert an und schreibt die niedrigwertigsten 8 Bit
  *          in den Adressbereich, der die LED-Ausgabe von D8-D15(GPIOs PD0 bis PD7) steuert.
  ******************************************************************************
  */
extern void write_phase_number_to_led();

/**
  ****************************************************************************** 
  * @author  Lasse Bruhn, Matr.-Nr.: 2880211
  * @brief   last_turn_forward() schaltet LED D23 an, last_turn_backward() LED22,
  *          show_error schaltet LED21 an
  ******************************************************************************
  */
extern void last_turn_forward();
extern void last_turn_backward();
extern void show_error();
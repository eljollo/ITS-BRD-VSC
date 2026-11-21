/**
 * @file display_output.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief Modul für die Ausgabe von Inhalten auf dem Display sowie für dessen
 * update.
 */

#ifndef DISPLAY_OUTPUT_H
#define DISPLAY_OUTPUT_H

// ============ KONSTANTEN ============
// für Displayausgabe
#define BUFF_SIZE 16
#define X_START_WRITE 1
#define Y_COORD_WRITE_ANGLE 3
#define Y_COORD_WRITE_SPEED 5
#define X_OFFSET_WRITE_ANGLE 30
#define X_OFFSET_WRITE_SPEED 30
#define MAX_INDEX 8

extern char angle_buff[BUFF_SIZE];
extern char speed_buff[BUFF_SIZE];

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   Printet initialen Inhalt auf Display.
 ******************************************************************************
 */
void init_display_output();

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   setzt Werte auf Display zurück auf 0.0 (Default).
 ******************************************************************************
 */
void reset_display();

/**
 ******************************************************************************
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @brief   printet je Superloop ein Zeichen auf das Display sofern Änderung zu
 * vorheriger Ziffer.
 ******************************************************************************
 */
void display_update(double angle, double speed);

#endif

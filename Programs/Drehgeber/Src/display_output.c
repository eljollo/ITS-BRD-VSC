/**
 ******************************************************************************
 * @file    display_output.c
 * @author  Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief   enthält Definitionen, bzw. Implementierungen der in display_output.h
 * deklarierten Funktionen
 ******************************************************************************
 */

// ============ INLCUDES ============
#include "display_output.h"
#include "lcd.h"
#include <stdbool.h>
#include <stdio.h>

// ============ Konstanten ============
char angle_buff[BUFF_SIZE];
char speed_buff[BUFF_SIZE];

static char old_angle_buff[BUFF_SIZE];
static char old_speed_buff[BUFF_SIZE];
static int index_write_from_array = 0;

static bool switch_output = false;

// ============ Display init ============
void init_display_output() {
   snprintf(angle_buff, sizeof(angle_buff), "%8.1f", 0.0);
   snprintf(speed_buff, sizeof(speed_buff), "%8.1f", 0.0);
   lcdGotoXY(X_START_WRITE, Y_COORD_WRITE_ANGLE);
   lcdPrintlnS("Winkel (in Grad):");
   lcdGotoXY(X_START_WRITE, Y_COORD_WRITE_SPEED);
   lcdPrintlnS("Geschwindigkeit (in Grad/s):");
   lcdGotoXY(X_OFFSET_WRITE_ANGLE, Y_COORD_WRITE_ANGLE);
   lcdPrintlnS(angle_buff);
   //    lcdGotoXY(X_OFFSET_WRITE_ANGLE + BUFF_SIZE, Y_COORD_WRITE_ANGLE);
   //    lcdPrintlnS("Grad");
   lcdGotoXY(X_OFFSET_WRITE_SPEED, Y_COORD_WRITE_SPEED);
   lcdPrintlnS(speed_buff);
   //    lcdGotoXY(X_OFFSET_WRITE_SPEED + BUFF_SIZE, Y_COORD_WRITE_SPEED);
   //    lcdPrintlnS("Grad/s");
}

// ============ Display reset ============
void reset_display() {
   snprintf(angle_buff, sizeof(angle_buff), "%8.1f", 0.0);
   snprintf(speed_buff, sizeof(speed_buff), "%8.1f", 0.0);
   lcdGotoXY(X_OFFSET_WRITE_ANGLE, Y_COORD_WRITE_ANGLE);
   lcdPrintlnS(angle_buff);
   lcdGotoXY(X_OFFSET_WRITE_SPEED, Y_COORD_WRITE_SPEED);
   lcdPrintlnS(speed_buff);
}

// ============ Display Ausgabe ============
void write_angle_on_display(double angle) {
   snprintf(angle_buff, sizeof(angle_buff), "%8.1f", angle);
   if (angle_buff[index_write_from_array] !=
       old_angle_buff[index_write_from_array]) {
      lcdGotoXY(X_OFFSET_WRITE_ANGLE + index_write_from_array,
                Y_COORD_WRITE_ANGLE);
      lcdPrintC(angle_buff[index_write_from_array]);
      old_angle_buff[index_write_from_array] =
          angle_buff[index_write_from_array];
   }
   index_write_from_array++;
   if (index_write_from_array == MAX_INDEX) {
      index_write_from_array = 0;
      switch_output = !switch_output;
   }
}

void write_speed_on_display(double speed) {
   snprintf(speed_buff, sizeof(speed_buff), "%8.1f", speed);
   if (speed_buff[index_write_from_array] !=
       old_speed_buff[index_write_from_array]) {
      lcdGotoXY(X_OFFSET_WRITE_SPEED + index_write_from_array,
                Y_COORD_WRITE_SPEED);
      lcdPrintC(speed_buff[index_write_from_array]);
      old_speed_buff[index_write_from_array] =
          speed_buff[index_write_from_array];
   }
   index_write_from_array++;
   if (index_write_from_array == MAX_INDEX) {
      index_write_from_array = 0;
      switch_output = !switch_output;
   }
}

void display_update(double angle, double speed) {
   if (!switch_output) {
      write_angle_on_display(angle);
   } else {
      write_speed_on_display(speed);
   }
}

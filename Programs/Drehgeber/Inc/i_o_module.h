/**
 * @file i_o_module.h
 * @author Thomas Ramba, Matr.Num.: 2842594
 * @date Nov 2026
 *
 * @brief .
 */

#ifndef IO_H
#define IO_H

#include "structs.h"
#include <stdbool.h>
#include <stdint.h>

void init_display_output(void);

void display_update();

void read_all_inputs();

void set_all_output(Direction direction, bool error, int phase_changes);

// ####################################################
// ####################################################
// ####################################################

#endif
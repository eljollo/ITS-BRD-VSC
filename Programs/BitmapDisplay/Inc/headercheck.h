#ifndef _HEADERCHECK_H
#define _HEADERCHECK_H 

#include "headers.h"
#include <errorhandler.h>
#include <stdint.h>
#include <BMP_types.h>

/**
 ******************************************************************************
 * @file    colors.h
 * @author  Lasse Bruhn, Matr.-Nr.: 2880211, Thomas Ramba Matr.nr.:
 * @brief   prüft anhand der ausgelesenen header-Infos, ob biBitCount == 8 und biCompression == 1
            holt Werte in structs file_hdr, info_hdr, holt aus diesen biCompression, biBitCount 
            und vergleicht diese mit Konstanten
 ******************************************************************************
 */

#define BIBITCOUNT 8
#define BICOMPRESSION 1
static BITMAPINFOHEADER info_hdr2;

int check_correct_format(BITMAPINFOHEADER *info_hdr);

#endif
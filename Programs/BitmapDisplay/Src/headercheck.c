
#include "BMP_types.h"
#include "MS_basetypes.h"
#include "errorhandler.h"
#include <headercheck.h>
#include <stdint.h>

//BITMAPINFOHEADER info_hdr2;

/**
 ******************************************************************************
 * @file    colors.h
 * @author  Lasse Bruhn, Matr.-Nr.: 2880211, Thomas Ramba Matr.nr.:
 * @brief   prüft anhand der ausgelesenen header-Infos, ob biBitCount == 8 und biCompression == 1
            holt Werte in structs file_hdr, info_hdr, holt aus diesen biCompression, biBitCount 
            und vergleicht diese mit Konstanten
 ******************************************************************************
 */



int check_correct_format(BITMAPINFOHEADER *info_hdr) {

    RETURN_ON_ERROR(get_info_hdr(info_hdr)); /* zweiten Header holen */
    CHECK_OR_RETURN(info_hdr->biBitCount==BIBITCOUNT && info_hdr->biCompression==BICOMPRESSION, UNSUPPORTED_FORMAT_ERR);
    return EOK;
} 
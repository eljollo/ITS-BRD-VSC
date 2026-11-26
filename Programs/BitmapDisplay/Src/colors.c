/**
 ******************************************************************************
 * @file    colors.c
 * @author  Lasse Bruhn, Matr.-Nr.: 2880211
 * @brief   contains Implementations for Declarations from colors.h
 ******************************************************************************
 */

#include "colors.h"

/**
 ******************************************************************************
 *          
 *  @author  Lasse Bruhn, Matr.-Nr.: 2880211
 *  @brief      Nimmt 4 Bytes als RGB-Farbwert an, shiftet um 8 Bit nach rechts zu 24 Bit 
                und konvertiert diesen in 16Bit-RGB-Wert (!liest keine Bytes aus bmp-datei deshalb bytes_to_display)
*   @param  uint32_t color
*   @retval uint16_t color_val
 ******************************************************************************
 */
 uint16_t farbkonvertierung(uint32_t color) {
    uint32_t rgb24 = color >> 8;                 // Reserved, dann Blau, Grün
    uint8_t red = (uint8_t)((rgb24 >> 16) & 0xFF); // Rot
    uint8_t green = (uint8_t)((rgb24 >>  8) & 0xFF); // Grün
    uint8_t blue = (uint8_t)( rgb24        & 0xFF); // Blau

    return (uint16_t)( ((uint32_t)(red >> 3) << 11)
                     | ((uint32_t)(green >> 2) <<  5)
                     | ((uint32_t)(blue >> 3)) );
 }
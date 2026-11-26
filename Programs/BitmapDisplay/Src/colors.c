/**
 ******************************************************************************
 * @file    colors.c
 * @author  Lasse Bruhn, Matr.-Nr.: 2880211
 * @brief   contains Implementations for Declarations from colors.h
 ******************************************************************************
 */

#include "colors.h"
#include "BMP_types.h"
#include <stdint.h>

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
    uint32_t rgb24 = color >> 8;                 // Reserved, dann Rot, Blau, Grün
    uint8_t red = (uint8_t)((rgb24 >> 16) & 0xFF); // Rot: 5 Byte
    uint8_t green = (uint8_t)((rgb24 >>  8) & 0xFF); // Grün: 6 Byte
    uint8_t blue = (uint8_t)( rgb24        & 0xFF); // Blau: 5 Byte

    return (uint16_t)( ((uint32_t)(red >> 3) << 11) | ((uint32_t)(green >> 2) <<  5)
                     | ((uint32_t)(blue >> 3)) );
 }

  /**
 ******************************************************************************
 *          
 *  @author  Lasse Bruhn, Matr.-Nr.: 2880211
 *  @brief      liest 4 Bytes aus Palettenbereich der BMP-Datei, ruft mit diesem Wert farbkonvertierung(uint32_t color) auf,
                und gibt den ermittelten 16Bit-Farbwert zurück
*   @param  uint32_t color (eher was anderes)
*   @retval uint16_t color_val
 ******************************************************************************
 */
 uint16_t bytes_to_display() {
    //byte-offset von dateistart bis pixelbereich ? wird durch nxt_chr()-Implementierung gesolved

 }

  /**
 ******************************************************************************
 *          
 *  @author  Lasse Bruhn, Matr.-Nr.: 2880211
 *  @brief      durchläuft Bytes im Palettenbereich der BMP-Datei und ruft dabei
                 (abh. von BITMAPINFOHEADER.abc ) bytes_to_display auf 
                 und schreibt Ergebnis in Array Farbpalette[current_index] von [0] - [255]
*   @param  uint32_t color
*   @retval uint16_t color_val
 ****************************************************************************** 
*/
void fill_farbpalette() {
    for (uint8_t i=0; i >= MAX_COLOR_TABLE_SIZE - 1; i++) {
        uint16_t color_val = bytes_to_display();
        farbpalette[i] = color_val;
    }
} 
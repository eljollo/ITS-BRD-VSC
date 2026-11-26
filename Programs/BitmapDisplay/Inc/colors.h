#include <stdint.h>
#include <BMP_types.h>
/**
 ******************************************************************************
 * @file    colors.h
 * @author  Lasse Bruhn, Matr.-Nr.: 2880211
 * @brief   enthält Farbkonvertierungsfunktionen, sowie das Array der verwendeten Farbpalette
 ******************************************************************************
 */

static uint16_t farbpalette[MAX_COLOR_TABLE_SIZE]; //wird mit fill_farbpalette bei jeder BMP-Verarbeitung neu befüllt
 
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
 uint16_t farbkonvertierung(uint32_t color);

  /**
 ******************************************************************************
 *          
 *  @author  Lasse Bruhn, Matr.-Nr.: 2880211
 *  @brief      liest 4 Bytes aus Palettenbereich der BMP-Datei, ruft mit diesem Wert farbkonvertierung(uint32_t color) auf,
                und gibt den ermittelten 16Bit-Farbwert zurück
*   @param  uint32_t color
*   @retval uint16_t color_val
 ******************************************************************************
 */
 uint16_t bytes_to_display();

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
void fill_farbpalette();
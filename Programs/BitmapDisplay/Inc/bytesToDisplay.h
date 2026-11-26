#include "MS_basetypes.h"
#include <colors.h>
#include <stdbool.h>
#include <stdint.h>
/**
 ******************************************************************************
 * @file    bytesToDisplay.h
 * @author  Lasse Bruhn, Matr.-Nr.: 2880211
 * @brief   Gibt RLE_8-codiertes Bitmap-Bild Pixelweise/Zeilenweise auf Display aus.
            Bündelt Aufrufe von lcdGUI_drawPoint() (und evtl.) lcdGUI_clear())
            Enthält Funktionen zum Auslesen der Bytes im Pixelbereich
*
*           -  
 ******************************************************************************
 */

 /**
 ******************************************************************************
 *          
 *  @author  Lasse Bruhn, Matr.-Nr.: 2880211
 *  @brief      prüft mit BITMAPINFOHEADER-Werten, ob aktuell verarbeitetes Bild(bzw. die Fläche in Pixeln davon)
                 zu groß für LCD-Display ist.
*   @param  int32_t bi_height, int32_t bi_width, ggf. als LONG-parameter annehmen und dann auf int32_t casten
*   @retval bool size_correct = false, wenn zu groß, sonst true
 ******************************************************************************
 */
 bool check_bitmap_size(LONG bi_height, LONG bi_width);

 /**
 ******************************************************************************
 *          
 *  @author  Lasse Bruhn, Matr.-Nr.: 2880211
 *  @brief      ruft check_bitmap_size(int32_t bi_height, int32_t bi_width) auf 
                und passt je nach return-Wert die Größe des darzustellenden Bildes an.
*   @param  int32_t bi_height, int32_t bi_width, ggf. als LONG-parameter annehmen und dann auf int32_t casten
*   @retval erstmal void
 ******************************************************************************
 */
void match_bitmap_size(LONG bi_height, LONG bi_width);

 /**
 ******************************************************************************
 *          
 *  @author  Lasse Bruhn, Matr.-Nr.: 2880211
 *  @brief      wird von draw_pixel() aufgerufen, wenn 1. gelesenes Byte nicht 0 ist.
                zeichnet anzahl der in byte1 angegebenen Pixel hintereinander(in zeile) in Farbe farbpalette[byte2] auf Display
*   @param  uint8_t byte1, uint8_t byte2
*   @retval erstmal void
 ******************************************************************************
 */
 void draw_pixel_encoded(uint8_t byte1, uint8_t byte2); 

 /**
 ******************************************************************************
 *          
 *  @author  Lasse Bruhn, Matr.-Nr.: 2880211
 *  @brief      wird von draw_pixel() aufgerufen, wenn 1. gelesenes Byte 0 ist.
                falls byte2 0,1 oder 2 ist, werden die jew. escape-Fälle umgesetzt.
                falls byte2 > 2, dann wird die entsprechende Anzahl an folgenden Bytes eingelesen, 
                und jew. ein Pixel auf das Display ausgegeben, der die Farbe farbpalette[(uint8_t)byte] hat.
*   @param  uint8_t byte1, uint8_t byte2
*   @retval erstmal void
 ******************************************************************************
 */ 
 void draw_pixel_absolute(uint8_t byte2);

 /**
 ******************************************************************************
 *          
 *  @author  Lasse Bruhn, Matr.-Nr.: 2880211
 *  @brief  Durchläuft Pixelbereich der BMP-Datei 
            liest 2 Bytes ein, erzeugt daraus 2 uint8_t-Werte und ruft, je nachdem wie diese sind, 
            entsprechend draw_pixel_encoded(uint8_t byte1, uint8_t byte2) oder draw_pixel_absolute(uint8_t byte2)
*   @param  void
*   @retval erstmal void
 ******************************************************************************
 */ 
 void draw_pixel(void);
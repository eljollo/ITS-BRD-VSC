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
 #include "LCD_general.h"
#include "MS_basetypes.h"
 #include "bytesToDisplay.h"

   /**
 ******************************************************************************
 *          
 *  @author  Lasse Bruhn, Matr.-Nr.: 2880211
 *  @brief  Gibt aktuell verarbeitetes Bild (pixelweise) auf LCD-Display aus.
            Ruft dafür die obigen Funktionen auf.
*   @param  void
*   @retval erstmal void
 ******************************************************************************
 */ 
void display_bitmap_per_pixel(void) {
    //match_bitmap_size(LONG bi_height, LONG bi_width);
}

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
 bool check_bitmap_size(LONG bi_height, LONG bi_width) {
    return ((LCD_X_MAXPIXEL >= bi_width) && (LCD_Y_MAXPIXEL >= bi_height));
 }

 

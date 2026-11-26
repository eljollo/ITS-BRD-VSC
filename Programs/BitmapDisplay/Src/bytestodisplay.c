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
/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUIDEMO_Bitmap.c
Purpose     : Draws bitmaps with and without compression
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "GUIDEMO.h"
#include <math.h>

#if GUI_WINSUPPORT
  #include "WM.h"
#endif

#define PI4 12.5663706f

/*********************************************************************
*
*       Terminator bitmap
*
**********************************************************************
*/
//#include"terminator.c"
extern const GUI_BITMAP bmterminator;
extern const GUI_BITMAP bmdelicous;
/*********************************************************************
*
*       GUIDEMO_Bitmap
*
**********************************************************************
*/

void GUIDEMO_Bitmap(void) {
  int XSize = LCD_GetXSize();
  int YSize = LCD_GetYSize();
  GUIDEMO_ShowIntro("Bitmaps",
                    "Showing"
                    "\nTerminator"
                    "\nSarah Connor Chronicles");
  GUI_SetBkColor(GUI_WHITE);
  GUI_SetColor(GUI_BLACK);
  GUI_Clear();
  GUI_DrawBitmap(&bmdelicous, 115,74); //refer photoshop for values
  GUI_DispStringAt("Bitmaps", 140, 170);
  GUI_DispStringAt("Created By Siddharth Kaul", 112,180 );
   GUI_DispStringAt("and Nandan Mehta",116,190);
  GUIDEMO_Delay(4000);
  GUIDEMO_Wait();
  #if GUI_WINSUPPORT & GUI_SUPPORT_MEMDEV
    WM_EnableMemdev(WM_HBKWIN);
  #endif
  #if GUIDEMO_LARGE
    GUI_DrawBitmap(&bmterminator, 0, 0);
    //GUI_SetFont(&GUI_Font13_1);
    //GUI_DispStringAt("RLE Compressed bitmaps", 10, 10);
    GUIDEMO_Wait();
    //GUI_Clear();
    //GUI_DispStringAt("1/2/4/8 bpp bitmaps", 10, 10);
    //GUI_DrawBitmap(&GUIDEMO_bm4bpp, 20, 50);
    GUIDEMO_Delay(4000);
    //GUIDEMO_NotifyStartNext();
    /* Tile display with image */
    /*
	{ 
      int ix, iy;
      for (ix = 0; ix < XSize / bmterminator.XSize + 1; ix++) {
        for (iy = 0; iy < YSize / bmterminator.YSize + 1; iy++) {
          GUI_DrawBitmap(&bmterminator, 
                         bmterminator.XSize * ix , 
                         bmterminator.YSize * iy);
        }
      }
    }*/
    /*
	GUIDEMO_Delay(2000);
    GUIDEMO_NotifyStartNext();
    GUIDEMO_ShowInfo("Bitmaps may also be\nmagnified and rotated");
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetFont(&GUI_Font16_1);
    */
	
	{
      /*
	  int i, tm;
      double xMul, Angle;
      for (i = 200; (i < 3000) && !GUIDEMO_CheckCancel();) {
        tm = GUI_GetTime();
        GUI_DrawBitmapEx(&bmterminator, XSize / 2, YSize / 2, bmterminator.XSize / 2, bmterminator.YSize / 2, i, i);
        GUI_DispStringHCenterAt("Bitmaps can be magnified...", XSize / 2, 100);
        GUI_Exec();
        while ((GUI_GetTime() < (tm + 10)) && !GUIDEMO_CheckCancel());
        i += (GUI_GetTime() - tm) * 6;
      }*/
      GUIDEMO_Delay(2000);
      /*
	  GUIDEMO_NotifyStartNext();
      GUI_Clear();
      GUI_DispStringHCenterAt("...and rotated.", XSize / 2, ((YSize + GUIDEMO_bm4bpp.YSize) >> 1) + 5);
      for (Angle = 0; Angle < PI4 && !GUIDEMO_CheckCancel();) {
        tm = GUI_GetTime();
        xMul = cos(Angle) * 1000;
        GUI_ClearRect((XSize - GUIDEMO_bm4bpp.XSize) >> 1, (YSize - GUIDEMO_bm4bpp.YSize) >> 1, (XSize + GUIDEMO_bm4bpp.XSize) >> 1, (YSize + GUIDEMO_bm4bpp.YSize) >> 1);
        GUI_DrawBitmapEx(&GUIDEMO_bm4bpp, XSize / 2, YSize / 2, GUIDEMO_bm4bpp.XSize / 2, GUIDEMO_bm4bpp.YSize / 2, xMul, 1000);
        GUI_Exec();
        while ((GUI_GetTime() < (tm + 10)) && !GUIDEMO_CheckCancel());
        Angle += (GUI_GetTime() - tm) / 250.0f;
      }
      GUI_DrawBitmapEx(&GUIDEMO_bm4bpp, XSize / 2, YSize / 2, GUIDEMO_bm4bpp.XSize / 2, GUIDEMO_bm4bpp.YSize / 2, 1000, 1000);
    }			   */
    }GUIDEMO_Wait();
  #else
    {/*
      const GUI_BITMAP * pBm;
      int TextModeOld = GUI_SetTextMode(GUI_TM_XOR);
      GUI_SetFont(&GUI_Font8_ASCII);
      pBm = &_bmLadyBug;
      GUI_DrawBitmap(pBm, (XSize - (int)pBm->XSize) / 2, (YSize - (int)pBm->YSize) / 2);
      GUI_DispStringAt("RLE Compressed bitmaps", 8, 10);
      GUIDEMO_Wait();
      GUI_Clear();
      GUI_SetTextMode(GUI_TM_TRANS);
      pBm = &GUIDEMO_bm4bpp;
      GUI_DrawBitmap(pBm, (XSize - (int)pBm->XSize) / 2, (YSize - (int)pBm->YSize) / 2);
      GUI_DispStringAt("1/2/4/8 bpp bitmaps", 8, 10);
      GUIDEMO_Wait();
      GUI_Clear();
      {
        int i, tm;
        double xMul, Angle;
        for (i = 200; (i < 2000) && !GUIDEMO_CheckCancel();) {
          tm = GUI_GetTime();
          GUI_DrawBitmapEx(&GUIDEMO_bm4bpp, XSize / 2, YSize / 2, GUIDEMO_bm4bpp.XSize / 2, GUIDEMO_bm4bpp.YSize / 2, i, i);
          GUI_DispStringAt("Bitmaps can be magnified...", 8, 10);
          GUI_Exec();
          while ((GUI_GetTime() < (tm + 10)) && !GUIDEMO_CheckCancel());
          i += (GUI_GetTime() - tm) * 6;
        }
        GUIDEMO_Delay(2000);
        GUIDEMO_NotifyStartNext();
        GUI_Clear();
        for (Angle = 0; Angle < PI4 && !GUIDEMO_CheckCancel();) {
          tm = GUI_GetTime();
          xMul = cos(Angle) * 1000;
          GUI_ClearRect((XSize - GUIDEMO_bm4bpp.XSize) >> 1, (YSize - GUIDEMO_bm4bpp.YSize) >> 1, (XSize + GUIDEMO_bm4bpp.XSize) >> 1, (YSize + GUIDEMO_bm4bpp.YSize) >> 1);
          GUI_DrawBitmapEx(&GUIDEMO_bm4bpp, XSize / 2, YSize / 2, GUIDEMO_bm4bpp.XSize / 2, GUIDEMO_bm4bpp.YSize / 2, xMul, 1000);
          GUI_DispStringAt("...and rotated.", 8, 10);
          GUI_Exec();
          while ((GUI_GetTime() < (tm + 10)) && !GUIDEMO_CheckCancel());
          Angle += (GUI_GetTime() - tm) / 250.0f;
        }
                GUI_DrawBitmapEx(&GUIDEMO_bm4bpp, XSize / 2, YSize / 2, GUIDEMO_bm4bpp.XSize / 2, GUIDEMO_bm4bpp.YSize / 2, 1000, 1000);
        GUI_DispStringAt("...and rotated.", 8, 10);
      }
      GUIDEMO_Wait();
      GUI_SetTextMode(TextModeOld);
    */}
  #endif
  #if GUI_WINSUPPORT & GUI_SUPPORT_MEMDEV
    WM_DisableMemdev(WM_HBKWIN);
  #endif
}

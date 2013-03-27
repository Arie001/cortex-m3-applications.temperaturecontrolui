/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
*        @internet: www.segger.com  @support: support@segger.com     *
*                                                                    *
**********************************************************************
*		@project 	BRAT - Begineers Researcher ARM Tablet								 *
* 	@module		Temperature Based Control UI													 *
*		@auth			Siddharath Kaul																				 *
*		@email		siddharth.kaul.k10@gmail.com | k10blogger@gmail.com		 *
*						(c) 2012 Siddharth Kaul and Nandan Mehta								 *
**********************************************************************
* Documented As For 21 March 2013:																	 *
* 				Siddharth Kaul																						 *
*																																		 *
**********************************************************************
*	@email: siddharth.kaul.k10@gmail.com												 			 *
* @email: nandanm.mehta@gmail.com															 			 *
* @site: 	code.google.com/p/cortex-m3-applications/						 			 *
**********************************************************************/

/*********************************************************************
* @description All Header Includes
*
**********************************************************************/
#include "DIALOG.h"
#include "GUI.h"
#include "PROGBAR.h"
#include "LPC17xx.h"
#include "LCD_ConfDefaults.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <STRING.h>

#include "tcpip.h"
/*********************************************************************
* @description All Global Variables 
*
**********************************************************************
*/
static PROGBAR_Handle ahProgBar[2];
unsigned int adcfinalvalue;
/*********************************************************************
* @description Main Dialog Ids
**********************************************************************/
#define ID_WINDOW_0    (GUI_ID_USER + 0x00)
#define ID_BUTTON_0    (GUI_ID_USER + 0x01)
#define ID_BUTTON_1    (GUI_ID_USER + 0x03)
#define ID_TEXT_0    (GUI_ID_USER + 0x09)
#define ID_TEXT_1    (GUI_ID_USER + 0x0B)
#define ID_PROGBAR_0    (GUI_ID_USER + 0x0C)
#define ID_PROGBAR_1    (GUI_ID_USER + 0x0D)
#define ID_BUTTON_2    (GUI_ID_USER + 0x0E)
#define ID_BUTTON_3    (GUI_ID_USER + 0x0F)
/*********************************************************************
* @description About Dialog Window Ids
**********************************************************************/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x11)
#define ID_TEXT_2 (GUI_ID_USER + 0x12)
#define ID_TEXT_3 (GUI_ID_USER + 0x13)
#define ID_TEXT_4 (GUI_ID_USER + 0x14)
#define ID_TEXT_5 (GUI_ID_USER + 0x15)
#define ID_TEXT_6 (GUI_ID_USER + 0x16)
#define ID_BUTTON_4 (GUI_ID_USER + 0x17)
/*********************************************************************
* @description Lan Setting Dialog Window Ids
**********************************************************************/
#define ID_FRAMEWIN_1 (GUI_ID_USER + 0x18)
//#define ID_TEXT_7 (GUI_ID_USER + 0x19)
#define ID_EDIT_0 (GUI_ID_USER + 0x1E)
//#define ID_TEXT_8 (GUI_ID_USER + 0x1F)
#define ID_EDIT_1 (GUI_ID_USER + 0x20)
//#define ID_TEXT_9 (GUI_ID_USER + 0x21)
#define ID_EDIT_2 (GUI_ID_USER + 0x22)
#define ID_BUTTON_5 (GUI_ID_USER + 0x23)
/*********************************************************************
* @description Resource Table
**********************************************************************/
/*********************************************************************
* @description Main Dialog Widget Components
**********************************************************************/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
 { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 320, 240, 0, 0 },
  { BUTTON_CreateIndirect, "Graph", ID_BUTTON_0, 227, 7, 80, 60, 0, 0 },
  { BUTTON_CreateIndirect, "Control", ID_BUTTON_1, 228, 78, 80, 60, 0, 0 },
  { TEXT_CreateIndirect, "Sensor", ID_TEXT_0, 17, 136, 43, 20, 0, 0 },
  { TEXT_CreateIndirect, "Valve", ID_TEXT_1, 18, 208, 40, 20, 0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 14, 154, 291, 20, 0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_1, 14, 185, 291, 20, 0, 0 },
  { BUTTON_CreateIndirect, "Lan Setting", ID_BUTTON_2, 139, 7, 80, 60, 0, 0 },
  { BUTTON_CreateIndirect, "About", ID_BUTTON_3, 139, 78, 80, 60, 0, 0 },
};
/**********************************************************************
* @description About Dialog Resource Table
***********************************************************************/
static const GUI_WIDGET_CREATE_INFO _aDialogCreateAbout[] = {
  { FRAMEWIN_CreateIndirect, "About", ID_FRAMEWIN_0, 34, 0, 241, 157, 0, 0 },
  { TEXT_CreateIndirect, "Temperature Control Version 1.125", ID_TEXT_2, 30, 0, 177, 20, 0, 0 },
  { TEXT_CreateIndirect, "Created By Siddharth Kaul and Nandan Mehta", ID_TEXT_3, 5, 19, 224, 20, 0, 0 },
  { TEXT_CreateIndirect, "Under Project Brat", ID_TEXT_4, 65, 37, 95, 20, 0, 0 },
  { TEXT_CreateIndirect, "Contact: siddharth.kaul.k10@gmail.com", ID_TEXT_5, 24, 58, 197, 20, 0, 0 },
  { TEXT_CreateIndirect, "Contact: nandanm.mehta@gmail.com", ID_TEXT_6, 24, 76, 184, 20, 0, 0 },
  { BUTTON_CreateIndirect, "Ok", ID_BUTTON_4, 79, 100, 80, 30, 0, 0 },
};
/***********************************************************************
* @description Lan Setting Dialog Box Resource Table
************************************************************************/
static const GUI_WIDGET_CREATE_INFO _aDialogCreateLan[] = {
  { FRAMEWIN_CreateIndirect, "Lan Settings", ID_FRAMEWIN_1, 0, 0, 273, 132, 0, 0 },
  { TEXT_CreateIndirect, "Subnet Mask", ID_TEXT_0, 0, 0, 80, 20, 0, 0 },
  { EDIT_CreateIndirect, "submask", ID_EDIT_0, 73, 0, 180, 20, 0, 100 },
  { TEXT_CreateIndirect, "Gateway", ID_TEXT_1, 0, 25, 80, 20, 0, 0 },
  { EDIT_CreateIndirect, "gateway", ID_EDIT_1, 73, 25, 180, 20, 0, 100 },
  { TEXT_CreateIndirect, "IP Address", ID_TEXT_2, 0, 50, 80, 20, 0, 0 },
  { EDIT_CreateIndirect, "ipaddress", ID_EDIT_2, 73, 50, 180, 20, 0, 100 },
  { BUTTON_CreateIndirect, "OK", ID_BUTTON_5, 90, 75, 80, 30, 0, 0 },
};
/***********************************************************************
* @description Extrenal Routine Prototypes
* @note For Complete File
************************************************************************/
extern unsigned int GetAD7Val(void);
extern void UART2_Init (void);
extern void UART2_SendString (unsigned char *s);
/***********************************************************************
* @description Internal Routine Prototypes
* @note For the Complete File
************************************************************************/
WM_HWIN CreateLan_Settings(void);
WM_HWIN CreateAbout(void);
WM_HWIN CreateWindow(void);
void DrawGraph(void);
void updateProg(void);
void assignfinalvalue(unsigned int value);
static void _Draw(void * p);
static void _Draw2(void * p);
static void _GetSineData(I16 * paY, int n);
static void _Label(void);
static void _GetRandomData(I16 * paY, int Time, int n) ;
static void _ShowText(const char * sText);
static void _LabelMS(void);
static void _DemoSineWave(void);
static void _DemoTemperatureGraph(void);
static void _getTemperatureData(I16 * paY, int n);
static void _DisplayTime(int tDiff);
/************************************************************************
* @description Callback Functions
*************************************************************************/
/************************************************************************
* @description Lan Dialog Box Callback Functions
*************************************************************************/
static void _cbDialogLan(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int Id, NCode;
	char my_ip_ids[15],my_temp[3];
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'submask'
    //
		sprintf(my_ip_ids,"%3u",SUBMASK_1);
		strcat(my_ip_ids,".");
    sprintf(my_temp,"%3u",SUBMASK_2);
		strcat(my_ip_ids,my_temp);
		strcat(my_ip_ids,".");
    sprintf(my_temp,"%3u",SUBMASK_3);
		strcat(my_ip_ids,my_temp);
		strcat(my_ip_ids,".");
    sprintf(my_temp,"%3u",SUBMASK_4);
		strcat(my_ip_ids,my_temp);
		//strcat(ip_ids,".");
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    //EDIT_SetText(hItem, my_ip_ids);
		//sprintf(my_ip_ids,"%15u",SubnetMask);
		EDIT_SetText(hItem, my_ip_ids);
    
		//
    // Initialization of 'gateway'
    //
		sprintf(my_ip_ids,"%3u",GWIP_1);
		strcat(my_ip_ids,".");
    sprintf(my_temp,"%3u",GWIP_2);
		strcat(my_ip_ids,my_temp);
		strcat(my_ip_ids,".");
    sprintf(my_temp,"%3u",GWIP_3);
		strcat(my_ip_ids,my_temp);
		strcat(my_ip_ids,".");
    sprintf(my_temp,"%3u",GWIP_4);
		strcat(my_ip_ids,my_temp);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
    //sprintf(my_ip_ids,"%15u",GatewayIP);
		EDIT_SetText(hItem, my_ip_ids);
    
		//
    // Initialization of 'ipaddress'
    //
		sprintf(my_ip_ids,"%3u",MYIP_1);
		strcat(my_ip_ids,".");
    sprintf(my_temp,"%3u",MYIP_2);
		strcat(my_ip_ids,my_temp);
		strcat(my_ip_ids,".");
    sprintf(my_temp,"%3u",MYIP_3);
		strcat(my_ip_ids,my_temp);
		strcat(my_ip_ids,".");
		sprintf(my_temp,"%3u",MYIP_4);
		strcat(my_ip_ids,my_temp);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
    //sprintf(my_ip_ids,"%15u",MyIP);
		EDIT_SetText(hItem, my_ip_ids);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_EDIT_0: // Notifications sent by 'submask'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_1: // Notifications sent by 'gateway'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_2: // Notifications sent by 'ipaddress'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_5: // Notifications sent by 'OK'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        GUI_EndDialog(pMsg->hWin, 0);
				// USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}
/************************************************************************
* @description About Dialog Box Callback Functions
*************************************************************************/
static void _cbDialogAbout(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int Id, NCode;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_4: // Notifications sent by 'Ok'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
				GUI_EndDialog(pMsg->hWin, 0);
				
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}
/************************************************************************
* @description Main Window Dialog Box Callback Functions
*************************************************************************/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int Id, NCode;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
		ahProgBar[0] = hItem;
		PROGBAR_SetMinMax(ahProgBar[0], 0, 100);
		PROGBAR_SetBarColor(ahProgBar[0], 0, GUI_RED);
		PROGBAR_SetBarColor(ahProgBar[0], 1, GUI_GREEN);
		PROGBAR_SetText(ahProgBar[0], "Temperature");
		PROGBAR_EnableMemdev(hItem);
		PROGBAR_SetMinMax(hItem, 0, 100);
		PROGBAR_SetBarColor(hItem, 0, GUI_GREEN);
		PROGBAR_SetValue(hItem, adcfinalvalue);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Graph'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
				
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
				//WM_DeleteWindow(pMsg->hWin);
				WM_HideWindow(pMsg->hWin);
				//GUI_EndDialog(pMsg->hWin, 0);
				DrawGraph();
				WM_ShowWindow(pMsg->hWin);
				//CreateWindow();
				//WM_Paint(pMsg->hWin);
				//updateProg();
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Control'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
				updateProg();
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Lan Setting'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
				CreateLan_Settings();
				updateProg();
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
		case ID_BUTTON_3: // Notifications sent by 'About'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
				/*
			   * @description Create About Dialog
			   */
				//GUI_CreateDialogBox(_aDialogCreateAbout, GUI_COUNTOF(_aDialogCreateAbout), &_cbDialogAbout, WM_HBKWIN, 34, 0);
				CreateAbout();
				updateProg();
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
		case WM_PAINT:
			/************************************************************************
			 * @note WM_CreateDialogBox or CreateWindow cannot be called in WM_Paint*
			 ************************************************************************/
			updateProg();
		break;
  default:
		
    WM_DefaultProc(pMsg);
    break;
  }
}
/************************************************************************
* @description Create Dialog Boxes Functions
*************************************************************************/
/************************************************************************
* @description Create Lan Dialog
*************************************************************************/
WM_HWIN CreateLan_Settings(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreateLan, GUI_COUNTOF(_aDialogCreateLan), &_cbDialogLan, WM_HBKWIN, 0, 0);
  return hWin;
}
/************************************************************************
* @description Create About Dialog
*************************************************************************/
WM_HWIN CreateAbout(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreateAbout, GUI_COUNTOF(_aDialogCreateAbout), &_cbDialogAbout, WM_HBKWIN, 34, 0);
  return hWin;
}
/************************************************************************
* @description Create Main Window Dialog
*************************************************************************/
WM_HWIN CreateWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, WM_HBKWIN, 0, 0);
	//GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	//GUI_Exec();
	return hWin;
}
/************************************************************************
* @description Updates Progress Bar
*************************************************************************/
void assignfinalvalue(unsigned int value)
{
	adcfinalvalue = value;
}
/************************************************************************
* @description Updates Progress Bar
*************************************************************************/
void updateProg()
{
		char temperature[4];
		char contString[20] = "Temperature ";
		//unsigned int adc_value_avg = adcfinalvalue;
		unsigned int i=0;
		sprintf(temperature, "%4u", adcfinalvalue);
		strcat(contString, temperature);
		strcat(contString," oC");
		//PROGBAR_SetMinMax(ahProgBar[0], 0, 100);
		PROGBAR_SetBarColor(ahProgBar[0], 0, GUI_RED);
		PROGBAR_SetBarColor(ahProgBar[0], 1, GUI_GREEN);
		PROGBAR_EnableMemdev(ahProgBar[0]);
		PROGBAR_SetText(ahProgBar[0], contString);
		PROGBAR_SetValue(ahProgBar[0], adcfinalvalue);
}
/************************************************************************
* @description The Second Part of Code Contains Graph Routines
* 
*************************************************************************/
/************************************************************************
* @description Macros Definition to be used in Creating Graph
* @note 
*************************************************************************/
// Vertical Ysize
#define YSIZE   (LCD_YSIZE - 100)
// Degree to radian constant
#define DEG2RAD (3.1415926f / 180)
// Graph Colors
#if LCD_BITSPERPIXEL == 1
  #define COLOR_GRAPH0 GUI_WHITE
  #define COLOR_GRAPH1 GUI_WHITE
#else
  #define COLOR_GRAPH0 GUI_GREEN
  #define COLOR_GRAPH1 GUI_YELLOW
#endif
/************************************************************************
* @description Structure Definition to store Y axis value of readings
* @note 
*************************************************************************/
typedef struct {
  I16 * aY;
} PARAM;
/************************************************************************
* @function _Draw
* @param Pointer to data
* @description 
*************************************************************************/
static void _Draw(void * p) {
  int i;
  PARAM * pParam = (PARAM *)p;
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetColor(GUI_DARKGRAY);
  GUI_ClearRect(19, (LCD_YSIZE - 20) - YSIZE, (LCD_XSIZE - 2), (LCD_YSIZE - 21));
  for (i = 0; i < (YSIZE / 2); i += 20) {
    GUI_DrawHLine((LCD_YSIZE - 20) - (YSIZE / 2) + i, 19, (LCD_XSIZE - 2));
    if (i) {
      GUI_DrawHLine((LCD_YSIZE - 20) - (YSIZE / 2) - i, 19, (LCD_XSIZE - 2));
    }
  }
  for (i = 40; i < (LCD_XSIZE - 20); i += 40) {
    GUI_DrawVLine(18 + i, (LCD_YSIZE - 20) - YSIZE, (LCD_YSIZE - 21));
  }
  GUI_SetColor(COLOR_GRAPH0);
  GUI_DrawGraph(pParam->aY, (LCD_XSIZE - 20), 19, (LCD_YSIZE - 20) - YSIZE);
}
/************************************************************************
* @function _Draw2
* @param Pointer to data
* @description 
*************************************************************************/
static void _Draw2(void * p) {
  PARAM * pParam = (PARAM *)p;
  _Draw(p);
  GUI_SetColor(COLOR_GRAPH1);
  GUI_DrawGraph(pParam->aY+15, (LCD_XSIZE - 20), 19, (LCD_YSIZE - 20) - YSIZE);
}
/************************************************************************
* @function _GetSineData
* @param 
* @description 
*************************************************************************/
static void _GetSineData(I16 * paY, int n) {
  int i;
  for (i = 0; i < n; i++) {
    float s = sin(i * DEG2RAD * 4);
    paY[i] = s * YSIZE / 2 + YSIZE / 2;
  }
}
/************************************************************************
* @function _Label
* @param 
* @description 
*************************************************************************/
static void _Label(void) {
  int x, y;
  GUI_SetPenSize(1);
  GUI_ClearRect(0, (LCD_YSIZE - 21) - YSIZE, (LCD_XSIZE - 1), (LCD_YSIZE - 1));
  GUI_DrawRect(18, (LCD_YSIZE - 21) - YSIZE, (LCD_XSIZE - 1), (LCD_YSIZE - 20));
  GUI_SetFont(&GUI_Font6x8);
  for (x = 0; x < (LCD_XSIZE - 20); x += 40) {
    int xPos = x + 18;
    GUI_DrawVLine(xPos, (LCD_YSIZE - 20), (LCD_YSIZE - 14));
    GUI_DispDecAt(x / 40, xPos - 2, (LCD_YSIZE - 9), 1);
  }
	/*
  for (y = 0; y < YSIZE / 2; y += 20) {
    int yPos = (LCD_YSIZE - 20) - YSIZE / 2 + y;
    GUI_DrawHLine(yPos, 13, 18);
    if (y) {
      GUI_GotoXY(1, yPos - 4);
      GUI_DispSDec(-y / 20, 2);
      yPos = (LCD_YSIZE - 20) - YSIZE / 2 - y;
      GUI_DrawHLine(yPos, 13, 18);
      GUI_GotoXY(1, yPos - 4);
      GUI_DispSDec(y / 20, 2);
    } else {
      GUI_DispCharAt('0', 7, yPos - 4);
    }
  }*/
	//YSIZE 140
	//LCd_YSIZE 240
	
	for(y = 80; y >= -80; y -= 20)
	{
			int yPos = (LCD_YSIZE - 20) - YSIZE / 2 + y;
			GUI_DrawHLine(yPos, 13, 18);
			GUI_GotoXY(1, yPos - 4);
			GUI_DispDec((80-y)*10 / 20, 2);
	}
}
/************************************************************************
* @function _GetRandomData
* @param 
* @description 
*************************************************************************/
static void _GetRandomData(I16 * paY, int Time, int n) {
  int aDiff, i;
  if (Time > 5000)
    Time -= 5000;
  if (Time > 2500)
    Time = 5000 - Time;
  Time /= 200;
  aDiff = Time * Time + 1;
  for (i = 0; i < n; i++) {
    if (!i) {
      paY[i] = rand() % YSIZE;
    } else {
      I16 yNew;
      int yD = aDiff - (rand() % aDiff);
      if (rand() & 1) {
        yNew = paY[i-1] + yD;
      } else {
        yNew = paY[i-1] - yD;
      }
      if (yNew > YSIZE) {
        yNew -= yD;
      } else { if (yNew < 0)
        yNew += yD;
      }
      paY[i] = yNew;
    }
  }
}
/************************************************************************
* @function _ShowText
* @param 
* @description 
*************************************************************************/
static void _ShowText(const char * sText) {
  GUI_SetColor(GUI_WHITE);
  GUI_SetBkColor(GUI_RED);
  GUI_ClearRect(0, 0, LCD_XSIZE, 60);
  GUI_SetFont(&GUI_FontComic18B_ASCII);
  GUI_DispStringAt(sText, 10, 20);
}
/************************************************************************
* @function _LabelMS
* @param 
* @description 
*************************************************************************/
static void _LabelMS(void) {
  GUI_SetFont(&GUI_Font6x8);
  GUI_DispStringAt("msec/graph:", 10, 50);
  
}
/************************************************************************
* @function _DisplayTime
* @param 
* @description 
*************************************************************************/
static void _DisplayTime(int tDiff) {
		GUI_GotoXY(80, 50);
    GUI_SetColor(GUI_WHITE);
    GUI_SetBkColor(GUI_RED);
    GUI_DispDecSpace(tDiff, 3);
}
/************************************************************************
* @function _getTemperatureData
* @param 
* @description 
*************************************************************************/
static void _getTemperatureData(I16 * paY, int n) {
	
	unsigned int i = 0;
	unsigned int adcV ;
					char temp_data[5];
	UART2_Init();
	for(i=0;i<n;i++)
	{
		/****************************************************
		 * @tried YSIZE + adcV/400 	@result no output
		 * @tried adcV/400 					@result output at 80 mark
		 * @tried 240 - (adcV/400) 	@result no output
		 * @tried adcV/40 					@result output at 60 mark
		 ****************************************************/
		adcV = GetAD7Val();
		/****************************************************
		 * @formula paY[i] = (adcV/40) + (YSIZE/2)
		 ****************************************************/
		paY[i] = YSIZE - (adcV/400);
		UART2_SendString("\nData For Graph: ");
		sprintf(temp_data,"%4u",paY[i]);
		UART2_SendString(temp_data);
	}
}
/************************************************************************
* @function _DemoTemperatureGraph
* @param 
* @description 
*************************************************************************/
static void _DemoTemperatureGraph(void) {
  PARAM Param;
	
	int samples = 0;
  unsigned int _exitNum = 0;
  GUI_RECT Rect = {19, (LCD_YSIZE - 20) - YSIZE, (LCD_XSIZE - 2), (LCD_YSIZE - 21)};
  GUI_HMEM hMem = GUI_ALLOC_AllocZero((LCD_XSIZE - 20) * sizeof(I16));
  _ShowText("Temperature vs Time graph");
  Param.aY = (I16*)GUI_ALLOC_h2p(hMem);
 
  GUI_SetFont(&GUI_Font6x8);
  GUI_DispStringAt("msec/graph:", 10, 50);
  
  _LabelMS();
  
  while(1) {
    
    GUI_PID_STATE TouchState;
		
		GUI_TOUCH_GetState(&TouchState);
		if (TouchState.Pressed) {
      _exitNum++;
     
    }
		/* NetWork Stuff */
		/* Graph continue*/
		
    _getTemperatureData(Param.aY,LCD_XSIZE - 20); //tDiff);//, (LCD_XSIZE - 20));
    GUI_MEMDEV_Draw(&Rect, _Draw, &Param, 0, GUI_MEMDEV_NOTRANS);
    _DisplayTime(samples);
		GUI_GotoXY(80, 50);
    GUI_SetColor(GUI_WHITE);
    GUI_SetBkColor(GUI_RED);
    GUI_DispDecSpace(samples, 3);
		++samples;
		/*****************************************************************
		* @note  Never Ever Put GUI_ALLOC_Free(hMem) here inside the loop.
		******************************************************************/
		if(_exitNum == 3)
			break;
  }
  GUI_ALLOC_Free(hMem);
}
/************************************************************************
* @function _DemoSineWave
* @param 
* @description 
*************************************************************************/
static void _DemoSineWave(void) {
  PARAM Param;
  I16 * pStart;
  int t0, Cnt = 0;
  GUI_RECT Rect = {19, (LCD_YSIZE - 20) - YSIZE, (LCD_XSIZE - 2), (LCD_YSIZE - 21)};
  GUI_HMEM hMem = GUI_ALLOC_AllocZero((LCD_XSIZE + 90) * sizeof(I16));
  _ShowText("Sine wave");
  pStart = (I16*)GUI_ALLOC_h2p(hMem);
	_getTemperatureData(pStart, LCD_XSIZE + 90);
  //_GetSineData(pStart, LCD_XSIZE + 90);
  /*
  GUI_SetFont(&GUI_Font6x8);
  GUI_DispStringAt("msec/graph:", 10, 50);
  */
  _LabelMS();
  t0 = GUI_GetTime();
  while(((GUI_GetTime() - t0) < 10000) ) {
    int t1, tDiff2;
    if (Cnt % 90) {
      Param.aY++;
    } else {
      Param.aY = pStart;
    }
    t1 = GUI_GetTime();
    GUI_MEMDEV_Draw(&Rect, _Draw2, &Param, 0, GUI_MEMDEV_NOTRANS);
    tDiff2 = GUI_GetTime() - t1;
    if (tDiff2 < 100) {
      GUI_Delay(100 - tDiff2);
    }
    if(!((++Cnt) % 10)) {
      _DisplayTime(tDiff2);
      /*
      GUI_GotoXY(80, 50);
      GUI_SetColor(GUI_WHITE);
      GUI_SetBkColor(GUI_RED);
      GUI_DispDecSpace(tDiff2, 3);
      */
    }
  }
  GUI_ALLOC_Free(hMem);
}
/************************************************************************
* @function DrawGraph
* @param 
* @description 
*************************************************************************/
void DrawGraph()
{
	GUI_Clear();
	_Label();
	_DemoTemperatureGraph();
	GUI_Clear();
}

/**************************** End of File ********************************/
/*************************************************************************
@signature Siddharth Kaul
**************************************************************************/

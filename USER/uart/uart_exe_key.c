/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**								   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           uart_main.c
** Last modified Date:  2012 October, 7
** Last Version:        V1.00
** Descriptions:        The uart_main() function
**
**--------------------------------------------------------------------------------------------------------
** Created by:          PowerAVR (C) Copyright.
** Created date:        2010-05-10
** Version:             V1.00
** Descriptions:        uart_main functiuon to be used in ucGUI
** Modified:			Siddharth Kaul
** Documented:			Nandan Mehta
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "LPC17xx.h"
#include "LCD_ConfDefaults.h"
#include "uart.h"
#include "GUI.h"
#include "GUIDEMO.h"
#include "Serial.h"
#include "BUTTON.h"
#include "EDIT.h"
#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))
char paste_to_screen[25];
/*********************************************************************************************************
** Function name:       _ExecKeyboard
** Descriptions:        Creates Delay
** input parameters:    ulTime
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
static unsigned char _acText[]={'1','2','3','4','5','6','7','8','9','0','=',
                         0,'Q','W','E','R','T','Y','U','I','O','P',
                         0,'A','S','D','F','G','H','J','K','L',':',
                         0,'Z','X','C','V','B','N','M','<','>','?',
                       ' ',' ',' ',' ',' ',0,0
					  };
int _ExecKeyboard_sidkaul(void) {
  int i;
  int Key;
  BUTTON_Handle ahButton[52];
  BUTTON_Handle hButtonESC;
  EDIT_Handle   hEdit;
  GUI_RECT rText = {000,0, LCD_XSIZE, 20};
  GUI_SetBkColor(GUI_BLUE);  
  GUI_Clear();
  GUI_DrawBitmap(&bmMicriumLogo, 0, 0);
  GUI_SetFont(&GUI_Font16B_1);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringInRect("µC/GUI", &rText, GUI_TA_RIGHT | GUI_TA_VCENTER);
  rText.y0 +=20;
  rText.y1 +=20;
  GUI_DispStringInRect("Touch screen Keypad", &rText, GUI_TA_RIGHT | GUI_TA_VCENTER);
  /* Create Keyboard Buttons */
  for (i=0; i< 51; i++) {
    int Pos = (i < 47) ? i : i+4;
    int x0 = 5  + 28*(Pos%11);
    int y0 = 100 + 28*(Pos/11);
    char c = _acText[i];
    int Id = c ? c : 1;
    char ac[2] = {0};
    char *s= ac;
    ac[0] = c;
    ahButton[i] = BUTTON_Create( x0, y0, 25, 25, Id,BUTTON_CF_SHOW );
    BUTTON_SetText   (ahButton[i], s);
    #if GUI_SUPPORT_MEMDEV
      BUTTON_EnableMemdev(ahButton[i]);
    #endif
  }
  ahButton[i] = BUTTON_Create( 89, 212, 109, 25, ' ',BUTTON_CF_SHOW );
  hButtonESC = BUTTON_Create( 230, 40, 80, 25, GUI_ID_CANCEL,BUTTON_CF_SHOW );
  BUTTON_SetText   (hButtonESC, "ESC");
  hEdit = EDIT_Create( 5, 70, 310, 25, ' ', 80, 0 );
  EDIT_SetFont(hEdit, &GUI_Font8x16);
  BUTTON_SetBkColor(ahButton[49], 0, GUI_RED);
  BUTTON_SetBkColor(ahButton[50], 0, GUI_BLUE);
  /* Handle Keyboard until ESC or ENTER is pressed */
  do {
    Key = GUIDEMO_WaitKey();
    switch (Key) {
    case 0:
    case GUI_ID_CANCEL:
     break;
    default:
      EDIT_AddKey(hEdit, Key);
    }
  } while ((Key != GUI_KEY_ENTER) && (Key!=GUI_ID_CANCEL) && (Key!=0));
  /* Cleanup */
  for (i=0; i< countof(ahButton); i++) {
    BUTTON_Delete(ahButton[i]);
  }
  BUTTON_Delete(hButtonESC);
  EDIT_Delete(hEdit);
  return Key;
}
/*********************************************************************************************************
** Function name:       Delay
** Descriptions:        Creates Delay
** input parameters:    ulTime
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Delay (uint32_t Time)
{
    uint32_t i;
    
    i = 0;
    while (Time--) {
        for (i = 0; i < 5000; i++);
    }
}

void uart_main(void)
{
	char temp;
	unsigned char total_x_chars,total_y_lines;
	unsigned int xsize,x,y,county,i;
	unsigned int ysize,temp_int;
	int ax_Phys[2],ay_Phys[2],key;
	SystemInit();
	UART2_Init();
	//UART2_Init();
	GUIDEMO_ShowIntro("UART Communication",
                    "Showing"
                    "\nUART Communication"
                    "\nBy Siddharth Kaul");
	GUI_Clear();
	GUI_SetBkColor(GUI_BLUE);
	GUI_SetColor(GUI_LIGHTRED);
	GUI_Clear();
	GUI_SetFont(&GUI_Font24B_1);
	//ydist = GUI_GetFontDistY();
	ysize = GUI_GetFontSizeY();
	total_x_chars = 320/24;
	total_y_lines = 240/24;
	x = 0;
	y = 0;
	county = 0;
	i = 0;
	UART2_SendString("Type any Words....\n");
	while (1) 
	{
		temp = UART2_GetChar();	
		xsize = GUI_GetCharDistX(temp);
		GUI_DispCharAt(temp, x, y);
		x = x + xsize;
		temp_int = temp;
		UART2_SendChar(temp_int);
		if(x>= 320)
		{
			county++;
			x = 0;
			
		}
		if(y >= 240)
		{
			do
			{
				GUI_PID_STATE State;
    			GUI_TOUCH_GetState(&State);
    			if (State.Pressed) 
				{
      				ax_Phys[0] = GUI_TOUCH_GetxPhys();
      				ay_Phys[0] = GUI_TOUCH_GetyPhys();
      				GUI_Clear();
					y = 0;
					county = 0;
					x = 0;
					break;
				}
			}while(1);//end of do while

			//GUI_Delay(5000);
		}
		y = county*ysize;
		
		//GUI_DispCharAt(U16 c, I16P x, I16P y);
		
		
		
		//UART2_SendString("Â·»¢£¨LandTiger£©UART²âÊÔ³ÌÐò\n");
		//UART2_SendString("http://www.PowerAVR.com\n");
		//UART2_SendString("http://www.PowerMCU.com\n");
        //Delay(3000);
    }
}
/******************************
**	Works perfectly fine
**	Key point requires 115200 baud rate
**	Less than it will result in trash value
**	Signing off Siddharth Kaul
**  Completed for show. Date 16 october 2012
*******************************/

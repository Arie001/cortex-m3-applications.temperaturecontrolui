/****************************************License ********************************************************
**                       Copyright (c) 2012 Siddharth Kaul and Nandan Mehta
** 
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
** associated documentation files (the "Software"), to deal in the Software without restriction, 
** including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
** subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial 
** portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
** NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
** WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
** SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
** 
**--------------File Info---------------------------------------------------------------------------------
** @File name:           uart_main.c
** @Last modified Date:  2012 October, 16
** @Last Version:        V1.00
** @Descriptions:        The uart_main() function
**
**--------------------------------------------------------------------------------------------------------
** @Created by:          Siddharth Kaul.
** @Created date:        2012 October, 7
** @Version:             V1.00
** @Descriptions:        uart_main functiuon to be used in ucGUI
** @Modified:		 Siddharth Kaul
** @Documented:		 Nandan Mehta
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "LPC17xx.h"
#include "LCD_ConfDefaults.h"
#include "uart.h"
#include "GUI.h"
#include "GUIDEMO.h"

/*********************************************************************************************************
** @Function name:       Delay
** @Descriptions:        Creates Delay
** @input parameters:    ulTime
** @output parameters:   None
** @Returned value:      None
*********************************************************************************************************/
void Delay (uint32_t Time)
{
    uint32_t i;
    
    i = 0;
    while (Time--) {
        for (i = 0; i < 5000; i++);
    }
}
/*********************************************************************************************************
** @Function name:       uart_main
** @Descriptions:        Main function of whole module
** @input parameters:    None
** @output parameters:   None
** @Returned value:      None
*********************************************************************************************************/

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
	
	do
	{
		GUI_PID_STATE State1;
		GUI_TOUCH_GetState(&State1);
		if (State1.Pressed) 
		{
			ax_Phys[0] = GUI_TOUCH_GetxPhys();
			ay_Phys[0] = GUI_TOUCH_GetyPhys();
			GUI_Clear();
			y = 0;
			county = 0;
			x = 0;

			break;
		
		}
		else
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
		}
	}while(1);//end of do while
	GUIDEMO_NotifyStartNext();
		
		//GUI_DispCharAt(U16 c, I16P x, I16P y);
		
		
		
		//UART2_SendString("UART Demo Example\n");
		//UART2_SendString("Created by Siddharth Kaul and Nandan Mehta\n");
		//UART2_SendString("Join our open source project.\n");
        //Delay(3000);
    
}
/******************************
** Works perfectly fine
** Key point requires 115200 baud rate
** Baud rate can be changed
** Less than it will result in trash value
** Signing off Siddharth Kaul
** Completed for show. Date 16 october 2012
*******************************/

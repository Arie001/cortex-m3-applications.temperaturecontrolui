/******************************
 ** show_bitmap
 **
 ******************************/
#include "GLCD_driver.h"
#include "GUI.h"
#include "GUIDEMO.h"
//#include "menu1.h"
extern unsigned char gImage_terminator_large[];
extern unsigned char gImage_britney[];
//extern void clear_buttons_and_frames();

void show_bitmap()
{
	
	
	int ax_Phys[2],ay_Phys[2],i;
	unsigned char *images[] = { gImage_terminator_large,
					gImage_britney
					};
	//clear_buttons_and_frames();
	
	GUIDEMO_ShowIntro("Photographic Bitmap",
                    "Showing"
                    "\nTerminator Sarah Connor Chronicles"
                    "\nBy Siddharth Kaul");
	GLCD_Init ();
  	GLCD_Clear (White);
	i = 0;
	do
	{
		GUI_PID_STATE State;
		GUI_TOUCH_GetState(&State);
		if (State.Pressed) 
		{
			GLCD_Clear(White);
		    GLCD_Bitmap(0, 0, 320, 240, images[i]);
			i++;
			if(i > 1)
			{
				i = 0;	
			}
			
			//break;
		}
	}while(1);//end of do while	
	//delete pointer to free up memory
	free(images);
	/*
	GUI_SetFont(&GUI_Font24B_1);
	GUI_SetColor(GUI_YELLOW);
	GUI_DispStringAt("Terminator", 0,0);*/
}
/*
 * button Test 1
 *
 */
#include <stddef.h>
#include "GUI.h"
#include "GUIDEMO.h"
#include "PROGBAR.h"
#include "LISTBOX.h"
#include "FRAMEWIN.h"
#include "BUTTON.h"
#include "menu1.h"
#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))
static BUTTON_Handle   _ahButton[7];
static FRAMEWIN_Handle _ahFrameWin[2];
static int             _ButtonSizeX,      _ButtonSizeY;
extern void show_bitmap();
extern int realtime();
static void _cb_framewin(WM_MESSAGE* pMsg)
{
 	//callback for frame window
	/*
	 * #info using BUTTON_IsPressed() function
	 * okay for checking button press.
	 * Take a temporary variable say check
	 * keep it equal to check = BUTTON_IsPressed(_ahButton[i])
	 * where i is the number of button in the array
	 * if check == 1 button is pressed 
	 * if check == 0 button is not pressed
	 * So code accordingly
	 * @SiddharthKaul
	 */
	unsigned int check,i=0;
	//UARt Communication
	do
	{
		check = BUTTON_IsPressed(_ahButton[i]);
		i++;
		if(i>6)
			i = 0;
	}while(check==0);
	if(i == 1)
		realtime();
	//if(i == 2)
		//show_bitmap();

}
void clear_buttons_and_frames()
{
	// Cleaning Buttons
	int i = 0;
	for (i = 0; i < countof(_ahButton); i++) {
      		BUTTON_Delete(_ahButton[i]);
    		}
	// Cleaning Frames
   FRAMEWIN_Delete(_ahFrameWin[1]);
}

void minimize_my_frame()
{
 	FRAMEWIN_Minimize(_ahFrameWin[1]);
}
void maximize_my_frame()
{
	FRAMEWIN_Maximize(_ahFrameWin[1]);
}
void restore_my_frame()
{
	FRAMEWIN_Restore(_ahFrameWin[1]);
}


void menu1_main()
{
 	int i = 0;
	_ButtonSizeX = 140;//maximum size 300;
    _ButtonSizeY = 40;//minimum size 20
    /* Create the control window incl. buttons */
    _ahFrameWin[0] = FRAMEWIN_Create("Menu", &_cb_framewin, WM_CF_SHOW | WM_CF_STAYONTOP,
                                                0,0, 320, 240);
    
	//_ahInfoWin[1] = WM_CreateWindowAsChild( 0, 0, 0, 0, WM_GetFirstChild(_ahFrameWin[1]), WM_CF_SHOW | WM_CF_STAYONTOP, &_cbCmdWin, 0);
    _ahButton[0] = BUTTON_CreateAsChild(5, 20, _ButtonSizeX, _ButtonSizeY, _ahFrameWin[1], 
                                        'S' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    _ahButton[1] = BUTTON_CreateAsChild(5, 70, _ButtonSizeX, _ButtonSizeY, _ahFrameWin[1], 
                                        'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
	_ahButton[2] = BUTTON_CreateAsChild(5, 120, _ButtonSizeX, _ButtonSizeY, _ahFrameWin[1], 
                                        'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    _ahButton[3] = BUTTON_CreateAsChild(150, 20, _ButtonSizeX, _ButtonSizeY, _ahFrameWin[1], 
                                        'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
	_ahButton[4] = BUTTON_CreateAsChild(150, 70, _ButtonSizeX, _ButtonSizeY, _ahFrameWin[1], 
                                        'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
	_ahButton[5] = BUTTON_CreateAsChild(150, 120, _ButtonSizeX, _ButtonSizeY, _ahFrameWin[1], 
                                        'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);

	BUTTON_SetText(_ahButton[0], "UART Communication");
    BUTTON_SetText(_ahButton[1], "Real Time Data Table");
	BUTTON_SetText(_ahButton[2], "Photos");
	BUTTON_SetText(_ahButton[3], "Clock");
	BUTTON_SetText(_ahButton[4], "USB Audio");
	BUTTON_SetText(_ahButton[5], "USB Host");
	//GUIDEMO_Delay(5000);
	/*
	 * #Note @Siddharth 
	 * Including while loop in this particular code hangs up the program.
	 * Try conditioning using non infinite loops.
	 *
	 */
	/*	while(1)
		{ 
		if(BUTTON_IsPressed(_ahButton[0]))
		{
			for (i = 0; i < countof(_ahButton); i++) {
      		BUTTON_Delete(_ahButton[i]);
    		}
			break;
		}
		}
	  */
	/*
	 *  Clean Up Command
	 */
	 /*
	for (i = 0; i < countof(_ahButton); i++) {
      BUTTON_Delete(_ahButton[i]);
    }  */

}
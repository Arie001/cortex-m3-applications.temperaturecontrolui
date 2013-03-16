/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : MainTask.c
Purpose     : Init GUI & call of GUI-demo
--------------------END-OF-HEADER-------------------------------------
*/

#include "GUI.h"
#include "GUIDEMO.h"
#include "WM.h"
extern void GUIDEMO_ShowColorBar(void);
extern void updateProg(void);
extern int realtime(void);
extern WM_HWIN CreateWindow(void);  
void MainTask(void) {
  GUI_Init();
	CreateWindow();
  while(1) {
		realtime();
		updateProg();
		GUI_Exec();
    //GUIDEMO_main();
		//GUIDEMO_ShowColorBar();
  }
}
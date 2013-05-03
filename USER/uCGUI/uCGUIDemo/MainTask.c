/**********************************************************************
*		@project 	BRAT - Begineers Researcher ARM Tablet									*
* 	@module		Temperature Based Control UI														*
*		@auth			Siddharath Kaul																					*
*		@email		siddharth.kaul.k10@gmail.com | k10blogger@gmail.com			*
*						(c) 2012 Siddharth Kaul and Nandan Mehta									*
***********************************************************************
*	@file        : MainTask.c																						*
* @purpose     : Init GUI & call of Starting Functions								*
*																																			*
*																																			*
***********************************************************************
* @description Includes all Required Files														*
***********************************************************************/
#include <includes.h>
#include "LPC17xx.h"
#include "GUI.h"
#include "GUIDEMO.h"
#include "WM.h"
/**********************************************************************
* @description Internal Routines Prototypes 													*
***********************************************************************/
void controlOutput(void);
/**********************************************************************
* @description External Routines Prototypes 													*
***********************************************************************/
extern void GUIDEMO_ShowColorBar(void);
extern void realtime_Init(void);
extern int realtime(void);
extern WM_HWIN CreateWindow(void);
extern void updateProg(void);
extern void UART2_Init (void);
extern unsigned int GetAD7Val(void);
extern void setDAC(uint16_t value);
extern void DACInit(void);
extern void UART2_SendString (unsigned char *s);
/**********************************************************************
* @name				 MainTask																								*
*	@param 			 None																										*
*	@return 		 None																										*
* @description External Routines Declaration													*
***********************************************************************/
void MainTask(void) {
  SystemInit();
	GUI_Init();
	UART2_Init();
	DACInit();
	CreateWindow();
	realtime_Init();
  while(1) {
		UART2_SendString ("Entered MainTask");
		updateProg();
		realtime();
			
		WM_ExecIdle();
		//GUI_Exec();
    //GUIDEMO_main();
		//GUIDEMO_ShowColorBar();
  }
}

/*************************** End of File *******************************/
/***********************************************************************
@signature Siddharth Kaul
************************************************************************/
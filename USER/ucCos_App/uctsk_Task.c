/**********************************************************************
*		@project 	BRAT - Begineers Researcher ARM Tablet									*
* 	@module		Temperature Based Control UI														*
*		@auth			Siddharath Kaul																					*
*		@email		siddharth.kaul.k10@gmail.com | k10blogger@gmail.com			*
*						(c) 2012 Siddharth Kaul and Nandan Mehta									*
***********************************************************************
*	@file        : uctsk_Task.c																					*
* @purpose     : 																											*
*																																			*
*																																			*
***********************************************************************
* @description Includes all Required Files														*
***********************************************************************/
#include <includes.h>            
/**********************************************************************
* @description Private variables 																			*
***********************************************************************/
static  OS_STK  App_Task_UCGUI_Stk         [APP_TASK_UCGUI_STK_SIZE];
static  OS_STK  App_Task_TouchPanel_Stk    [APP_TASK_TouchPanel_STK_SIZE];
static  OS_STK  App_Task_RealTime_Stk      [APP_TASK_RealTime_STK_SIZE];
static  OS_STK	App_Task_DrawGraph_Stk 	   [APP_TASK_DrawGraph_STK_SIZE];
/**********************************************************************
* @description Internal Function Prototype														*
***********************************************************************/
       void MainTask         		(void);
static void uctsk_UCGUI      		(void);
static void uctsk_TouchPanel 		(void);
static void uctsk_RealTime	 		(void);
static void uctsk_DrawGraph  		(void);
/**********************************************************************
* @description External Routine Prototype															*
***********************************************************************/
extern void _ExecCalibration (void);
extern int  realtime				 (void);
extern void DrawGraph				 (void);
extern void realtime_Init	   (void);
/**********************************************************************
* @name 				App_UCGUI_TaskCreate																	*
*	@param 				None																									*
*	@return				None																									*
* @description 	One-Line-Description																	*
***********************************************************************/
void App_UCGUI_TaskCreate(void)
{
  CPU_INT08U  os_err;
	os_err = os_err; 
	/*****************************************************
	**	@description ucGUI Task Create and Initialisation*
	******************************************************/
	os_err = OSTaskCreate((void (*)(void *)) uctsk_UCGUI,				
  (void          * ) 0,							
  (OS_STK        * )&App_Task_UCGUI_Stk[APP_TASK_UCGUI_STK_SIZE - 1],		
  (INT8U           ) APP_TASK_UCGUI_PRIO  );							
	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_UCGUI_PRIO, "Task UCGUI", &os_err);
	#endif
  /**********************************************************
	**	@description TouchPanel Task Create and Initialisation*
	***********************************************************/
	os_err = OSTaskCreate((void (*)(void *)) uctsk_TouchPanel,				
  (void          * ) 0,							
  (OS_STK        * )&App_Task_TouchPanel_Stk[APP_TASK_TouchPanel_STK_SIZE - 1],		
  (INT8U           ) APP_TASK_TouchPanel_PRIO  );
	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_TouchPanel_PRIO, "TASK TouchPanel Messages", &os_err);
	#endif
	/********************************************************
	**	@description RealTime Task Create and Initialisation*
	*********************************************************/
	os_err = OSTaskCreate((void (*)(void *)) uctsk_RealTime,				
  (void          * ) 0,							
  (OS_STK        * )&App_Task_RealTime_Stk[APP_TASK_RealTime_STK_SIZE - 1],		
  (INT8U           ) APP_TASK_RealTime_PRIO  );
	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_RealTime_PRIO, "TASK RealTime", &os_err);
	#endif
	/********************************************************
	**	@description DrawGraph Task Create and Initialisation*
	*********************************************************/
	os_err = OSTaskCreate((void (*)(void *)) uctsk_DrawGraph,				
  (void          * ) 0,							
  (OS_STK        * )&App_Task_DrawGraph_Stk[APP_TASK_DrawGraph_STK_SIZE - 1],		
  (INT8U           ) APP_TASK_DrawGraph_PRIO  );
	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_RealTime_PRIO, "TASK DrawGraph", &os_err);
	#endif
	
}							 
/**********************************************************************
* @name 				uctsk_UCGUI																						*
*	@param 				None																									*
*	@return				None																									*
* @description 	One-Line-Description																	*
***********************************************************************/
static void uctsk_UCGUI (void) 
{   
   GUI_Init();
   _ExecCalibration();
   	for(;;)
   	{  
	  MainTask(); 
    }
}
/**********************************************************************
* @name 				uctsk_RealTime																				*
*	@param 				None																									*
*	@return				None																									*
* @description 	One-Line-Description																	*
***********************************************************************/
static void uctsk_RealTime (void)
{
		realtime_Init();
		while(1)
		{
			realtime();
		}
}
/**********************************************************************
* @name 				uctsk_TouchPanel																			*
*	@param 				None																									*
*	@return				None																									*
* @description 	One-Line-Description																	*
***********************************************************************/
static void uctsk_TouchPanel (void) 
{  
    TP_Init();

   	for(;;)
   	{  
	   GUI_TOUCH_Exec();
	   OSTimeDlyHMSM(0, 0, 0, 20);	 /* 20 MS  */
    }
}
/**********************************************************************
* @name 				uctsk_DrawGraph																				*
*	@param 				None																									*
*	@return				None																									*
* @description 	One-Line-Description																	*
***********************************************************************/
static void uctsk_DrawGraph (void)
{
	GUI_Init();	
	DrawGraph();
	while(1)
	{
		GUI_Exec();
	}
}

/************************ END FILE ************************************/
/**********************************************************************
@signature Siddharth Kaul
***********************************************************************/

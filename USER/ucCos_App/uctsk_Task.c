/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               uctsk_Task.c
** Descriptions:            The uctsk_Task application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-24
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <includes.h>            


/* Private variables ---------------------------------------------------------*/
static  OS_STK         App_Task_UCGUI_Stk        [APP_TASK_UCGUI_STK_SIZE];
static  OS_STK         App_Task_TouchPanel_Stk   [APP_TASK_TouchPanel_STK_SIZE];
static  OS_STK         App_Task_RealTime_Stk   [APP_TASK_RealTime_STK_SIZE];
static  OS_STK				 App_Task_DrawGraph_Stk [APP_TASK_DrawGraph_STK_SIZE]; 

/* Private function prototypes -----------------------------------------------*/
       void MainTask         (void);
static void uctsk_UCGUI      (void);
static void uctsk_TouchPanel (void);
extern void _ExecCalibration (void);
static void uctsk_RealTime	 (void);
extern int  realtime				 (void);
extern void DrawGraph				 (void);
static void uctsk_DrawGraph  (void);
extern void realtime_Init	   (void);
void  App_UCGUI_TaskCreate 	 (void)
{
    CPU_INT08U  os_err;

	os_err = os_err; 

	os_err = OSTaskCreate((void (*)(void *)) uctsk_UCGUI,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_Task_UCGUI_Stk[APP_TASK_UCGUI_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_UCGUI_PRIO  );							

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_UCGUI_PRIO, "Task UCGUI", &os_err);
	#endif
   
    os_err = OSTaskCreate((void (*)(void *)) uctsk_TouchPanel,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_Task_TouchPanel_Stk[APP_TASK_TouchPanel_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_TouchPanel_PRIO  );

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_TouchPanel_PRIO, "TASK TouchPanel Messages", &os_err);
	#endif
	 
	 os_err = OSTaskCreate((void (*)(void *)) uctsk_RealTime,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_Task_RealTime_Stk[APP_TASK_RealTime_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_RealTime_PRIO  );

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_RealTime_PRIO, "TASK RealTime", &os_err);
	#endif

	os_err = OSTaskCreate((void (*)(void *)) uctsk_DrawGraph,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_Task_DrawGraph_Stk[APP_TASK_DrawGraph_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_DrawGraph_PRIO  );

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_RealTime_PRIO, "TASK DrawGraph", &os_err);
	#endif 
}							 


static void uctsk_UCGUI (void) 
{   
   GUI_Init();
   _ExecCalibration();	  /* ´¥ÃþÆÁÐ£×¼   */
   	for(;;)
   	{  
	  MainTask(); 
    }
}

static void uctsk_RealTime (void)
{
		realtime_Init();
		while(1)
		{
			realtime();
		}
}
static void uctsk_TouchPanel (void) 
{  
    TP_Init();

   	for(;;)
   	{  
	   GUI_TOUCH_Exec();
	   OSTimeDlyHMSM(0, 0, 0, 20);	 /* 20 MS  */
    }
}
static void uctsk_DrawGraph (void)
{
	GUI_Init();	
	DrawGraph();
	while(1)
	{
		GUI_Exec();
	}
		
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

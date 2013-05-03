/**********************************************************************
*		@project 	BRAT - Begineers Researcher ARM Tablet									*
* 	@module		Temperature Based Control UI														*
*		@auth			Siddharath Kaul																					*
*		@email		siddharth.kaul.k10@gmail.com | k10blogger@gmail.com			*
*						(c) 2012 Siddharth Kaul and Nandan Mehta									*
***********************************************************************
*	@file        : app_cfg.h																						*
* @purpose     : 																											*
*																																			*
*																																			*
***********************************************************************/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__
					  

/**********************************************************************
* @description Macros Definition - Module Enable/Disable							*
***********************************************************************/
#define  DEF_DISABLED                    0
#define  DEF_ENABLED                     1

/**********************************************************************
* @description DEF_ENABLED = Present, DEF_DISABLED = Not Present      *
***********************************************************************/
#define  OS_VIEW_MODULE                  DEF_DISABLED	     	
/**********************************************************************
* @description Macros Definition - Task Names													*
***********************************************************************/

/**********************************************************************
* @description Macros Definition - Task Priorities										*
***********************************************************************/
#define  OS_VIEW_TASK_PRIO               (2)
#define  APP_TASK_BACKLIGHT_PRIO         (3) 
#define  APP_TASK_TouchPanel_PRIO		 		 (4)
#define  APP_TASK_UCGUI_PRIO             (5)
#define  APP_TASK_RealTime_PRIO					 (6)
#define  APP_TASK_DrawGraph_PRIO				 (7)
#define  APP_TASK_BLINK_PRIO          	 (OS_LOWEST_PRIO - 4)


#define  APP_TASK_START_PRIO                               1
#define  APP_TASK_OSVIEW_TERMINAL_PRIO	 (OS_LOWEST_PRIO - 6)
#define  OS_TASK_TMR_PRIO                (OS_LOWEST_PRIO - 2)
/************************************************************************************************
* @description Macros Definition - Task Stack Size Size of the task stacks (# of OS_STK entries)*
*************************************************************************************************/
#define  APP_TASK_UCGUI_STK_SIZE             512u 
#define  APP_TASK_BACKLIGHT_STK_SIZE				 64u
#define  APP_TASK_TouchPanel_STK_SIZE				 128u
#define  APP_TASK_BLINK_STK_SIZE             128u
#define  APP_TASK_RealTime_STK_SIZE				 	 256u
#define  APP_TASK_DrawGraph_STK_SIZE				 256u
#define  APP_TASK_START_STK_SIZE              64u
#define  APP_TASK_OSVIEW_TERMINAL_STK_SIZE	 256u
#define  OS_VIEW_TASK_STK_SIZE               256u

/**********************************************************************
* @description Macros Definition - Libraries													*
***********************************************************************/
#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED

#endif
/*************************** End of File *******************************/
/***********************************************************************
@signature Siddharth Kaul
************************************************************************/

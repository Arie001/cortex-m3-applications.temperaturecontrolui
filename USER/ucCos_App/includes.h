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
***********************************************************************/

#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__
/**********************************************************************
* @description Includes all Required Header Files											*
***********************************************************************/
#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <math.h>

#include  <uCOS-II\Source\ucos_ii.h>
#include  <uCOS-II\Ports\ARM-Cortex-M3\RealView\os_cpu.h>
#include  <uC-CPU\ARM-Cortex-M3\RealView\cpu.h>

#if (OS_VIEW_MODULE == DEF_ENABLED)
#include    <uCOS-VIEW\Ports\ARM-Cortex-M3\Realview\os_viewc.h>
#include    <uCOS-VIEW\Source\os_view.h>
#endif

#include    <GUI.h>
#include    "LPC17xx.h"
#include    "TouchPanel.h"
#include    "LCDConf.h"
#include    "GLCD.h"

#endif
/************************ END FILE ************************************/
/**********************************************************************
@signature Siddharth Kaul
***********************************************************************/




/****************************************************************************
 *   @Name: rtc_main.c
 *
 *   #Description:
 *     This file contains RTC main executable function.
 *
 ****************************************************************************
 * Copyright (c) 2012 Siddharth Kaul and Nandan Mehta
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 ****************************************************************************/
#include "LPC17xx.h"
#include "system_LPC17xx.h"
#include "type.h"
#include "rtc.h"
#include "GUI.h"
#include "GUIDEMO.h" 
extern volatile uint32_t alarm_on;
RTCTime local_time, alarm_time, current_time;

/*****************************************************************************
**   Main Function  rtc_main()
******************************************************************************/
void rtc_main (void)
{ 
  /* SystemClockUpdate() updates the SystemFrequency variable */
  SystemCoreClockUpdate();

  /* Initialize RTC module */
  RTCInit();
  GUIDEMO_ShowIntro("Real Time Clock",
                    "Showing"
                    "\nReal Time Clock"
                    "\nBy Siddharth Kaul");
	GUI_Clear();
	GUI_SetBkColor(GUI_BLUE);
	GUI_SetColor(GUI_LIGHTRED);
	GUI_Clear();
	GUI_SetFont(&GUI_Font24B_1);
  local_time.RTC_Sec = 0;
  local_time.RTC_Min = 0;
  local_time.RTC_Hour = 0;
  local_time.RTC_Mday = 8;
  local_time.RTC_Wday = 3;
  local_time.RTC_Yday = 12;		/* current date 07/12/2006 */
  local_time.RTC_Mon = 7;
  local_time.RTC_Year = 2006;
  RTCSetTime( local_time );		/* Set local time */

  alarm_time.RTC_Sec = 0;
  alarm_time.RTC_Min = 0;
  alarm_time.RTC_Hour = 0;
  alarm_time.RTC_Mday = 1;
  alarm_time.RTC_Wday = 0;
  alarm_time.RTC_Yday = 1;		/* alarm date 01/01/2007 */
  alarm_time.RTC_Mon = 1;
  alarm_time.RTC_Year = 2007;
  RTCSetAlarm( alarm_time );		/* set alarm time */

  NVIC_EnableIRQ(RTC_IRQn);

  /* mask off alarm mask, turn on IMYEAR in the counter increment interrupt
  register */
  RTCSetAlarmMask(AMRSEC|AMRMIN|AMRHOUR|AMRDOM|AMRDOW|AMRDOY|AMRMON|AMRYEAR);
  LPC_RTC->CIIR = IMMIN | IMYEAR;
  /* 2007/01/01/00:00:00 is the alarm on */
    
  RTCStart();

  while (1) 
  {					/* Loop forever */
	current_time = RTCGetTime();
	{
	  	char rtc_sec,rtc_min,rtc_hour;
		rtc_sec = current_time.RTC_Sec;
		rtc_min = current_time.RTC_Min;
		rtc_hour = current_time.RTC_Hour;
		GUI_DispCharAt(rtc_sec, 10, 10);
	  	GUI_DispCharAt(rtc_min, 14, 20);
	  	GUI_DispCharAt(rtc_hour, 18, 30);
	 }	
	}
  

}

/******************************************************************************
**                            End Of File
******************************************************************************/

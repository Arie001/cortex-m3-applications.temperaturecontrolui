/******************************************************************
 *****                                                        *****
 *****  Name: realtime.c                                       *****
 *****  Ver.: 1.0                                             *****
 *****  Date: 07/05/2001                                      *****
 *****  Auth: Andreas Dannenberg                              *****
 *****        HTWK Leipzig                                    *****
 *****        university of applied sciences                  *****
 *****        Germany                                         *****
 *****  Func: implements a dynamic HTTP-server by using       *****
 *****        the easyWEB-API                                 *****
 *****                                                        *****
 ******************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DIALOG.h"
#include "GUI.h"
#include "PROGBAR.h"
#include "LPC17xx.h"      // Keil: Register definition file for LPC17xx
#include "GUI.h"
#include "GUIDEMO.h"
#include "FRAMEWIN.h"
#include "BUTTON.h"
#include "TEXT.h"
#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))
#define extern            // Keil: Line added for modular project management

#include "realtime.h"

#include "type.h"
#include "EMAC.h"         // Keil: *.c -> *.h    // ethernet packet driver
#include "tcpip.h"        // Keil: *.c -> *.h    // easyWEB TCP/IP stack

//#include "webpage.h"                             // webside for our HTTP server (HTML)
#include "real_time_data_window.h"
//#include "menu1.h"
unsigned int pagecounter = 100;
unsigned int adcValue    =   0;
unsigned int sensor_value_1 = 0;
unsigned int sensor_value_2 = 0;
unsigned int sensor_value_3 = 0;
//extern uint32_t SystemFrequency = IRC_OSC;
extern void TCPClockHandler(void);
//extern void clear_buttons_and_frames();
volatile DWORD TimeTick  = 0;
//extern void minimize_my_frame();
//extern void restore_my_frame();
/* SysTick interrupt happens every 10 ms */

//static LISTVIEW_Handle _ahListView[1];
static int             _ButtonSizeX,      _ButtonSizeY;
void SysTick_Handler_realtime (void) {
  TimeTick++;
  if (TimeTick >= 20) {
    TimeTick = 0;
    LPC_GPIO2->FIOPIN ^= 1 << 0;
    TCPClockHandler();  
  }  
}
//void create_ui();
void increment_sensor_value_1()
{
 	++sensor_value_1;
}
void increment_sensor_value_2()
{
 	++sensor_value_2;
}
void increment_sensor_value_3()
{
 	++sensor_value_3;
}
void decrement_sensor_value_1()
{
	--sensor_value_1;
	if(sensor_value_1<1)
		sensor_value_1 = 0;
}
void decrement_sensor_value_2()
{
	--sensor_value_2;
	if(sensor_value_2<1)
		sensor_value_2 = 0;
}
void decrement_sensor_value_3()
{
	--sensor_value_3;
	if(sensor_value_3<1)
		sensor_value_3 = 0;
}

extern void updateProg(void);

//void main(void)
int realtime(void)
{
//InitOsc();              // Keil: No oscillator initialization necessary at this time.
//InitPorts();			  // Keil: No port initialization necessary at this time.
  //minimize_my_frame();
  
  //GUI_Clear();
  //GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, WM_HBKWIN, 0, 0);
  //GUI_Clear();
  
  /*
  GUI_Clear();
  GUI_SetBkColor(GUI_BLUE);
  GUI_SetColor(GUI_LIGHTRED);
  GUI_Clear();
  GUI_SetFont(&GUI_Font24B_1);
  GUI_DispStringAt("Real Time WebPage", 0, 0);
  GUI_DispStringAt("Created By Siddharth Kaul",0,24);
  GUI_DispStringAt("and Nandan Mehta", 0, 48);
  GUI_DispStringAt("Enter 192.168.1.11 in ur web browsser and see the magic", 0, 72);
  */
  SystemInit();                                      /* setup core clocks */
  //SysTick_Config(SystemFrequency/100);               /* Generate interrupt every 10 ms */
  SysTick_Config(SystemCoreClock/100);
  SysTick_Handler_realtime ();
  LPC_GPIO0->FIODIR   |= 1 << 21;					// ÉèÖÃLEDÓÐÐ§
  LPC_GPIO0->FIOPIN	  |= 1 << 21;

  LPC_GPIO2->FIODIR   |= 1 << 0;                    /* P2.0 defined as Output (LED) */

  LPC_PINCON->PINSEL3 |=  (3ul<<30);                   /* P1.31 is AD0.5 */
  LPC_SC->PCONP       |=  (1<<12);                   /* Enable power to ADC block */
  LPC_ADC->ADCR        =  (1<< 5) |                  /* select AD0.5 pin */
                          (4<< 8) |                  /* ADC clock is 25MHz/5 */
                          (1<<21);                   /* enable ADC */ 

  TCPLowLevelInit();
  
/*
  *(unsigned char *)RemoteIP = 24;               // uncomment those lines to get the
  *((unsigned char *)RemoteIP + 1) = 8;          // quote of the day from a real
  *((unsigned char *)RemoteIP + 2) = 69;         // internet server! (gateway must be
  *((unsigned char *)RemoteIP + 3) = 7;          // set to your LAN-router)

  TCPLocalPort = 2025;
  TCPRemotePort = TCP_PORT_QOTD;
  TCPActiveOpen();
  

  while (SocketStatus & SOCK_ACTIVE)             // read the quote from memory
  {                                              // by using the hardware-debugger
    DoNetworkStuff();
  }
*/
  //TCPActiveOpen();
  HTTPStatus = 0;                                // clear HTTP-server's flag register

  TCPLocalPort = TCP_PORT_HTTP;                  // set port we want to listen to
  
  	//do
	//{
		
		//GUI_PID_STATE State;
		//create_ui();
		//GUI_TOUCH_GetState(&State);
	while(1)
	{
	 	//key = 0;
		//CreateWindow();
		WM_ExecIdle();
		if (!(SocketStatus & SOCK_ACTIVE)) TCPPassiveOpen();   // listen for incoming TCP-connection
		DoNetworkStuff();                                      // handle network and easyWEB-stack
		SysTick_Handler_realtime ();                                                       // events
		HTTPServer();
		//GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
		WM_ExecIdle();
		//updateProg();
		

	}
		
		
		//while(key!=GUI_ID_BUTTON0 || key!=GUI_ID_BUTTON1 || key!=GUI_ID_BUTTON2 || key!=GUI_ID_BUTTON3
		// || key!=GUI_ID_BUTTON4 || key!=GUI_ID_BUTTON5);
		//if (State.Pressed) 
		//{
			//ax_Phys[0] = GUI_TOUCH_GetxPhys();
			//ay_Phys[0] = GUI_TOUCH_GetyPhys();
			//restore_my_frame();
			//GUIDEMO_Wait();
			//create_ui();
	  
    		//WM_ExecIdle();
			//break;
		//}
		//else
		//{
		    //delete_window();
			//create_ui();
			//if (!(SocketStatus & SOCK_ACTIVE)) TCPPassiveOpen();   // listen for incoming TCP-connection
    		//DoNetworkStuff();                                      // handle network and easyWEB-stack
    		//SysTick_Handler_realtime ();                                                       // events
    		//HTTPServer();
			//WM_ExecIdle();
			//WM_ExecIdle();
		//}
		
	//}while(1);//end of do while
}

// This function implements a very simple dynamic HTTP-server.
// It waits until connected, then sends a HTTP-header and the
// HTML-code stored in memory. Before sending, it replaces
// some special strings with dynamic values.
// NOTE: For strings crossing page boundaries, replacing will
// not work. In this case, simply add some extra lines
// (e.g. CR and LFs) to the HTML-code.
void HTTPServer(void)
{
  if (SocketStatus & SOCK_CONNECTED)             // check if somebody has connected to our TCP
  {
    if (SocketStatus & SOCK_DATA_AVAILABLE)      // check if remote TCP sent data
      TCPReleaseRxBuffer();                      // and throw it away

    if (SocketStatus & SOCK_TX_BUF_RELEASED)     // check if buffer is free for TX
    {
      if (!(HTTPStatus & HTTP_SEND_PAGE))        // init byte-counter and pointer to webside
      {                                          // if called the 1st time
        HTTPBytesToSend = sizeof(WebSide) - 1;   // get HTML length, ignore trailing zero
        PWebSide = (unsigned char *)WebSide;     // pointer to HTML-code
      }
	  
      if (HTTPBytesToSend > MAX_TCP_TX_DATA_SIZE)     // transmit a segment of MAX_SIZE
      {
        if (!(HTTPStatus & HTTP_SEND_PAGE))           // 1st time, include HTTP-header
        {
          memcpy(TCP_TX_BUF, GetResponse, sizeof(GetResponse) - 1);
          memcpy(TCP_TX_BUF + sizeof(GetResponse) - 1, PWebSide, MAX_TCP_TX_DATA_SIZE - sizeof(GetResponse) + 1);
          HTTPBytesToSend -= MAX_TCP_TX_DATA_SIZE - sizeof(GetResponse) + 1;
          PWebSide += MAX_TCP_TX_DATA_SIZE - sizeof(GetResponse) + 1;
        }
        else
        {
          memcpy(TCP_TX_BUF, PWebSide, MAX_TCP_TX_DATA_SIZE);
          HTTPBytesToSend -= MAX_TCP_TX_DATA_SIZE;
          PWebSide += MAX_TCP_TX_DATA_SIZE;
        }
          
        TCPTxDataCount = MAX_TCP_TX_DATA_SIZE;   // bytes to xfer
        InsertDynamicValues();                   // exchange some strings...
        //completeWebPage();
		TCPTransmitTxBuffer();                   // xfer buffer
      }
      else if (HTTPBytesToSend)                  // transmit leftover bytes
      {
        memcpy(TCP_TX_BUF, PWebSide, HTTPBytesToSend);
        TCPTxDataCount = HTTPBytesToSend;        // bytes to xfer
        InsertDynamicValues();					 // exchange some strings...
		//completeWebPage();                   
        TCPTransmitTxBuffer();                   // send last segment
        TCPClose();                              // and close connection
        HTTPBytesToSend = 0;                     // all data sent
      }
	  
      HTTPStatus |= HTTP_SEND_PAGE;              // ok, 1st loop executed
      
	}
  }
  else
    HTTPStatus &= ~HTTP_SEND_PAGE;               // reset help-flag if not connected
}

// samples and returns the AD-converter value of channel 2

unsigned int GetAD7Val(void)
{
// Keil: function replaced to handle LPC1768 A/D converter.
  unsigned int val;

  LPC_ADC->ADCR |=  (1<<24);                     /* start conversion */
  while (!(LPC_ADC->ADGDR & (1UL<<31)));         /* Wait for Conversion end */
  val = ((LPC_ADC->ADGDR >> 4) & 0xFFF);         /* read converted value */
  LPC_ADC->ADCR &= ~(7<<24);                     /* stop conversion */

  return(val);                                   /* result of A/D process */ 
}

// searches the TX-buffer for special strings and replaces them
// with dynamic values (AD-converter results)
void assignfinalvalue(unsigned int value);
void InsertDynamicValues(void)
{
  unsigned char *Key;
           char NewKey[5];
  unsigned int i;
	unsigned int adcvalarray[10],numinc;
  
  if (TCPTxDataCount < 4) return;                     // there can't be any special string
  
  Key = TCP_TX_BUF;
  
  for (i = 0; i < (TCPTxDataCount - 3); i++)
  {
    if (*Key == 'A')
     if (*(Key + 1) == 'D')
       if (*(Key + 2) == '%')
         switch (*(Key + 3))
         {
           case '1' :                                 // "AD8%"?
           {
             for(numinc=0;numinc<10;numinc++)
						 {
							 adcvalarray[numinc] = GetAD7Val();
						 }
						 for(numinc=0;numinc<10;numinc++)
						 {
							 adcValue = adcValue + adcvalarray[i];
						 }
						 adcValue = adcValue/400;  // get AD value
						 assignfinalvalue(adcValue);
             sprintf(NewKey, "%3u", adcValue);       // insert AD converter value
             memcpy(Key, NewKey, 3);
			 *(Key + 3) = ' ';                  
             break;
           }
           case '2' :                                 // "AD7%"?
           {
             adcValue = sensor_value_2;                  // get AD value
             //sprintf(NewKey, "%3u", (adcValue*100)/4024);     // copy saved value from previous read
             sprintf(NewKey, "%3u", adcValue);     // copy saved value from previous read
             memcpy(Key, NewKey, 3);
			 *(Key + 3) = ' ';                 
             break;
           }
		   case '3' :                                 // "AD1%"?
           {
 			 adcValue = sensor_value_3;                  // get AD value
             sprintf(NewKey, "%3u",adcValue);    // increment and insert page counter
             //memcpy(NewKey,"Created By Siddharth Kaul and Nandan Mehta",50);
			 memcpy(Key, NewKey, 3);
			 *(Key + 3) = ' ';  
			 //*(Key + 4) = ' ';  
             break;
           }
         }
    Key++;
  }
}

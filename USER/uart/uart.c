/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**				   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** @File name:           uart.c
** @Last modified Date:  2010-05-12
** @Last Version:        V1.00
** @Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** @Created by:          PowerAVR
** @Created date:        2010-05-10
** @Version:             V1.00
** @Descriptions:        
** @Modified by:	 Siddharth Kaul and Nandan Mehta
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "lpc17xx.h"                              /* LPC17xx definitions    */
#include "uart.h"

#define FOSC                        12000000                            

#define FCCLK                      (FOSC  * 8)                          
                                                                        
#define FCCO                       (FCCLK * 3)                          
                                                                        
#define FPCLK                      (FCCLK / 4)                          
                                                                        

/*********************************************************************************************************
 ** #info set baud rate of individual uart terminals
 **
 ********************************************************************************************************/
#define UART0_BPS     115200                                             
#define UART2_BPS     115200                                             
/*********************************************************************************************************
** Function name:       UART0_Init
** Descriptions:        
** input parameters:    None
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void UART0_Init (void)
{
	uint16_t usFdiv;
    /* UART0 */
    LPC_PINCON->PINSEL0 |= (1 << 4);             /* Pin P0.2 used as TXD0 (Com0) */
    LPC_PINCON->PINSEL0 |= (1 << 6);             /* Pin P0.3 used as RXD0 (Com0) */
  
  	LPC_UART0->LCR  = 0x83;                      /* 允许设置波特率               */
    usFdiv = (FPCLK / 16) / UART0_BPS;           /* 设置波特率                   */
    LPC_UART0->DLM  = usFdiv / 256;
    LPC_UART0->DLL  = usFdiv % 256; 
    LPC_UART0->LCR  = 0x03;                      /* 锁定波特率                   */
    LPC_UART0->FCR  = 0x06; 				   
}

/*********************************************************************************************************
** @Function name:       UART0_SendByte
** @Descriptions:        
** @input parameters:    integer ucData (byte to be send)
** @output parameters:   None
** @Returned value:      None
*********************************************************************************************************/
int UART0_SendByte (int ucData)
{
	while (!(LPC_UART0->LSR & 0x20));
    return (LPC_UART0->THR = ucData);
}

/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
int UART0_GetChar (void) 
{
  	while (!(LPC_UART0->LSR & 0x01));
  	return (LPC_UART0->RBR);
}

/*********************************************************************************************************
** #info Write character to Serial Port
** @Function name:       UART0_SendString
** @Descriptions:	
** @input parameters:    String pointer/array pointer
** @output parameters:   None
** @Returned value:      None
*********************************************************************************************************/
void UART0_SendString (unsigned char *s) 
{
  	while (*s != 0) 
	{
   		UART0_SendByte(*s++);
	}
}

/*********************************************************************************************************
** @Function name:       UART2_Init
** @Descriptions:        
** @input parameters:    None
** @output parameters:   None
** @Returned value:      None
*********************************************************************************************************/
void UART2_Init (void)
{
	uint16_t usFdiv;
    /* UART2 */
    LPC_PINCON->PINSEL0 |= (1 << 20);             /* Pin P0.10 used as TXD2 (Com2) */
    LPC_PINCON->PINSEL0 |= (1 << 22);             /* Pin P0.11 used as RXD2 (Com2) */

   	LPC_SC->PCONP = LPC_SC->PCONP|(1<<24);	      /*打开UART2电源控制位	           */

    LPC_UART2->LCR  = 0x83;                       /* 允许设置波特率                */
    usFdiv = (FPCLK / 16) / UART2_BPS;            /* 设置波特率                    */
    LPC_UART2->DLM  = usFdiv / 256;
    LPC_UART2->DLL  = usFdiv % 256; 
    LPC_UART2->LCR  = 0x03;                       /* 锁定波特率                    */
    LPC_UART2->FCR  = 0x06;
}

/*********************************************************************************************************
** @Function name:       UART2_SendByte
** @Descriptions:        
** @input parameters:    int data byte data to be send
** @output parameters:   None
** @Returned value:      None
*********************************************************************************************************/
int UART2_SendByte (int ucData)
{
	while (!(LPC_UART2->LSR & 0x20));
    return (LPC_UART2->THR = ucData);
}

/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
char UART2_GetChar (void) 
{
  	while (!(LPC_UART2->LSR & 0x01));
  	return (LPC_UART2->RBR);
}

/*********************************************************************************************************
** #info Write character to Serial Port
** @Function name:       UART2_SendString
** @Descriptions:	    
** @input parameters:    String pointer
** @output parameters:   None
** @Returned value:      None
*********************************************************************************************************/
void UART2_SendString (unsigned char *s) 
{
  	while (*s != 0) 
	{
   		UART2_SendByte(*s++);
	}
}
void UART2_SendChar(char disp)
{
	uint16_t dispbuf[4];
	uint8_t i;

	dispbuf[3] = disp%10 + '0';
	dispbuf[2] = disp/10%10 + '0';
	dispbuf[1] = disp/10/10%10 + '0';
	dispbuf[0] = disp/10/10/10%10 + '0';
	for(i=0;i<4;i++)
		UART2_SendByte(dispbuf[i]);
}
void UART0_SendChar(uint16_t disp)
{
	uint16_t dispbuf[4];
	uint8_t i;

	dispbuf[3] = disp%10 + '0';
	dispbuf[2] = disp/10%10 + '0';
	dispbuf[1] = disp/10/10%10 + '0';
	dispbuf[0] = disp/10/10/10%10 + '0';
	for(i=0;i<4;i++)
		UART0_SendByte(dispbuf[i]);	
}

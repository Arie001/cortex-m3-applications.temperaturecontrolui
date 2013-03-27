/**********************************************************************
*		@project 	BRAT - Begineers Researcher ARM Tablet									*
* 	@module		Temperature Based Control UI														*
*		@auth			Siddharath Kaul																					*
*		@email		siddharth.kaul.k10@gmail.com | k10blogger@gmail.com			*
*						(c) 2012 Siddharth Kaul and Nandan Mehta									*
***********************************************************************
*	@file        : debug.c																							*
* @purpose     : 																											*
*																																			*
*																																			*
***********************************************************************
* @description Includes all Required Files														*
***********************************************************************/
#include "lpc17xx.h"
/**********************************************************************
* @description Macros Definition 																			*
***********************************************************************/
#define FOSC                        12000000                            
#define FCCLK                      (FOSC  * 8)                          
#define FCCO                       (FCCLK * 3)                          
#define FPCLK                      (FCCLK / 4)  
/**********************************************************************
* @description set baud rate of individual uart terminals							*
***********************************************************************/
#define UART0_BPS     115200                                             
#define UART2_BPS     115200                                             
/**********************************************************************
* @description Internal Function Prototype														*
***********************************************************************/
void UART0_Init (void);
int  UART0_SendByte (int ucData);
int  UART0_GetChar (void);
void UART0_SendString (unsigned char *s); 
void UART2_Init (void);
int  UART2_SendByte (int ucData);
char  UART2_GetChar (void);
void UART2_SendString (unsigned char *s);
void UART0_SendChar(uint16_t disp); 
/**********************************************************************
* @name 				UART0_Init																						*
*	@param 				None																									*
*	@return				None																									*
* @description 	One-Line-Description																	*
***********************************************************************/
void UART0_Init (void)
{
	uint16_t usFdiv;
    /* UART0 */
    LPC_PINCON->PINSEL0 |= (1 << 4);  /* Pin P0.2 used as TXD0 (Com0) */
    LPC_PINCON->PINSEL0 |= (1 << 6);  /* Pin P0.3 used as RXD0 (Com0) */
  
  	LPC_UART0->LCR  = 0x83;                      
    usFdiv = (FPCLK / 16) / UART0_BPS;           
    LPC_UART0->DLM  = usFdiv / 256;
    LPC_UART0->DLL  = usFdiv % 256; 
    LPC_UART0->LCR  = 0x03;                      
    LPC_UART0->FCR  = 0x06; 				   
}
/**********************************************************************
* @name 				UART0_SendByte																				*
*	@param 				None																									*
*	@return				None																									*
* @description 	One-Line-Description																	*
***********************************************************************/
int UART0_SendByte (int ucData)
{
	while (!(LPC_UART0->LSR & 0x20));
    return (LPC_UART0->THR = ucData);
}
/**********************************************************************
* @name 				UART0_GetChar																					*
*	@param 				None																									*
*	@return				int																										*
* @description 	Read character from Serial Port   (blocking read)			*
***********************************************************************/
int UART0_GetChar (void) 
{
  	while (!(LPC_UART0->LSR & 0x01));
  	return (LPC_UART0->RBR);
}
/**********************************************************************
* @name 				UART0_SendString																			*
*	@param 				None																									*
*	@return				int																										*
* @description 	Write character to Serial Port												*
***********************************************************************/
void UART0_SendString (unsigned char *s) 
{
  	while (*s != 0) 
	{
   		UART0_SendByte(*s++);
	}
}
/**********************************************************************
* @name 				UART0_SendChar																				*
*	@param 				None																									*
*	@return				int																										*
* @description 	Write character to Serial Port												*
***********************************************************************/
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
/**********************************************************************
* @name 				UART2_Init																						*
*	@param 				None																									*
*	@return				int																										*
* @description 	Write character to Serial Port												*
***********************************************************************/
void UART2_Init (void)
{
	uint16_t usFdiv;
    /* UART2 */
    LPC_PINCON->PINSEL0 |= (1 << 20); /* Pin P0.10 used as TXD2 (Com2) */
    LPC_PINCON->PINSEL0 |= (1 << 22); /* Pin P0.11 used as RXD2 (Com2) */

   	LPC_SC->PCONP = LPC_SC->PCONP|(1<<24);	      

    LPC_UART2->LCR  = 0x83;                       
    usFdiv = (FPCLK / 16) / UART2_BPS;            
    LPC_UART2->DLM  = usFdiv / 256;
    LPC_UART2->DLL  = usFdiv % 256; 
    LPC_UART2->LCR  = 0x03;                       
    LPC_UART2->FCR  = 0x06;
}
/**********************************************************************
* @name 				UART2_SendByte																				*
*	@param 				None																									*
*	@return				int																										*
* @description 	Write character to Serial Port												*
***********************************************************************/
int UART2_SendByte (int ucData)
{
	while (!(LPC_UART2->LSR & 0x20));
    return (LPC_UART2->THR = ucData);
}
/**********************************************************************
* @name 				UART2_SendByte																				*
*	@param 				None																									*
*	@return				int																										*
* @description 	Read character from Serial Port   (blocking read)			*
***********************************************************************/
char UART2_GetChar (void) 
{
  	while (!(LPC_UART2->LSR & 0x01));
  	return (LPC_UART2->RBR);
}
/**********************************************************************
* @name 				UART2_SendString																			*
*	@param 				None																									*
*	@return				int																										*
* @description 	Write character to Serial Port												*
***********************************************************************/
void UART2_SendString (unsigned char *s) 
{
  	while (*s != 0) 
	{
   		UART2_SendByte(*s++);
	}
}
/**********************************************************************
* @name 				UART2_SendChar																				*
*	@param 				None																									*
*	@return				int																										*
* @description 	Write character to Serial Port												*
***********************************************************************/
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
/************************ END FILE ************************************/
/**********************************************************************
@signature Siddharth Kaul
***********************************************************************/
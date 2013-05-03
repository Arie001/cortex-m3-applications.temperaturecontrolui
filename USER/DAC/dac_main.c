/**********************************************************************
*		@project 	BRAT - Begineers Researcher ARM Tablet									*
* 	@module		Temperature Based Control UI														*
*		@auth			Siddharath Kaul																					*
*		@email		siddharth.kaul.k10@gmail.com | k10blogger@gmail.com			*
*						(c) 2012 Siddharth Kaul and Nandan Mehta									*
***********************************************************************
*	@file        : dac_main.c																						*
* @purpose     : 																											*
*																																			*
*																																			*
***********************************************************************
* @description Includes all Required Files														*
***********************************************************************/
#include "LPC17xx.h"

/**********************************************************************
* @description Macros Definition - Module Enable/Disable							*
***********************************************************************/

/**********************************************************************
* @description External Routines Prototypes 													*
***********************************************************************/

/**********************************************************************
* @description Internal Routines Prototypes 													*
***********************************************************************/
void DACInit(void);
void showSine(void);
void showSquare(void);
void showTriangle(void);
void setDAC(uint16_t value);
/**********************************************************************
* @name				 DACInit																								*
*	@param 			 None																										*
*	@return 		 None																										*
* @description External Routines Declaration													*
***********************************************************************/
void DACInit( void )
{
  /* setup the related pin to DAC output */
  LPC_PINCON->PINSEL1 = 0x00200000;	/* set p0.26 to DAC output */   
  return;
}
/**********************************************************************
* @name				 setDAC																								*
*	@param 			 None																										*
*	@return 		 None																										*
* @description External Routines Declaration													*
***********************************************************************/
void setDAC( uint16_t value )
{
	DACInit();
	LPC_DAC->DACR = (value<<6); 
}
/**********************************************************************
* @name				 setDAC																								*
*	@param 			 None																										*
*	@return 		 None																										*
* @description External Routines Declaration													*
***********************************************************************/
void controlOutput(uint16_t value)
{
	if(value<25)
	{
		DACInit();
		LPC_DAC->DACR = (310<<6);
	}
	else if(value>=25 && value<=50 )
	{
		DACInit();
		LPC_DAC->DACR = (620<<6);
	}
	else
	{
		DACInit();
		LPC_DAC->DACR = (930<<6);
	}
}
/**********************************************************************
* @description Various Waveforms																			*
***********************************************************************/

/**********************************************************************
* @description Sine Waveforms																					*
***********************************************************************/
volatile uint16_t SinTable[45] =                                       
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};
/**********************************************************************
* @name				 showSine																								*
*	@param 			 None																										*
*	@return 		 None																										*
* @description One Line Description 																	*
***********************************************************************/
void showSine()
{
	volatile unsigned int i =0;
	for (i = 0; i < 45; i++)
	{	
		LPC_DAC->DACR = (SinTable[i] << 6);      
  }
}
/**********************************************************************
* @description Square Waveforms																				*
***********************************************************************/
volatile uint16_t SquareTable[10] =
{
	900,0,900,0,900,0,900,0,900,0
};
/**********************************************************************
* @name				 showSquare																							*
*	@param 			 None																										*
*	@return 		 None																										*
* @description One Line Description																		*
***********************************************************************/
void showSquare()
{
	volatile unsigned int i =0;
	for (i = 0; i < 10; i++)
	{	
		LPC_DAC->DACR = (SquareTable[i]);      
  }
}
/**********************************************************************
* @description Triangle Waveforms																			*
***********************************************************************/
volatile uint16_t TriangleTable[10] =
{
	900,0,900,0,900,0,900,0,900,0
};
/**********************************************************************
* @name				 showTriangle																						*
*	@param 			 None																										*
*	@return 		 None																										*
* @description One Line Description																		*
***********************************************************************/
void showTriangle()
{
	volatile unsigned int i =0;
	for (i = 0; i < 10; i++)
	{	
		LPC_DAC->DACR = (TriangleTable[i]);      
  }
}

/************************ END FILE ************************************/
/**********************************************************************
@signature Siddharth Kaul
***********************************************************************/

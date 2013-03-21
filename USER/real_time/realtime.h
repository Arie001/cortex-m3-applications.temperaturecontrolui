/***************************************************************************
*	@project 	BRAT - Begineers Researcher ARM Tablet		   *
* 	@module		Temperature Based Control UI			   *
*	@auth		Siddharath Kaul					   *
*	@email		siddharth.kaul.k10@gmail.com | k10blogger@gmail.com*
*		(c) 2012 Siddharth Kaul and Nandan Mehta		   *
****************************************************************************
* @file        	: realtime.c						   *
* @purpose     	: implements a dynamic HTTP-server by using the easyWEB-API*                        																											*
* @auth 	: Andreas Dannenberg					   *
* @note		: Andreas Dannenberg is the original Creator of this file  *
*		  The file has been adapted to use.			   *
****************************************************************************/
#ifndef __EASYWEB_H

#define __EASYWEB_H


const unsigned char GetResponse[] =  // 1st thing our server sends to a client

{
  "HTTP/1.0 200 OK\r\n"             // protocol ver 1.0, code 200, reason OK
  
   "Content-Type: text/html\r\n"     // type of data we want to send
  
   "\r\n"                            // indicate end of HTTP-header

};


/***************************************************************************
* @description Internal Function Prototypes				   *
****************************************************************************/
void InitOsc(void);                              // prototypes

void InitPorts(void);

void HTTPServer(void);

void InsertDynamicValues(void);

unsigned int GetAD7Val(void);

unsigned int GetTempVal(void);


unsigned char *PWebSide;                         // pointer to webside

unsigned int HTTPBytesToSend;                    // bytes left to send


unsigned char HTTPStatus;                        // status byte 

#define HTTP_SEND_PAGE               0x01        // help flag


#endif

/*************************** END FILE ***************************************/
/****************************************************************************
@signature Siddharth Kaul
*****************************************************************************/

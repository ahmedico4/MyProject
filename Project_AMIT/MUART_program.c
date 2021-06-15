/************************************************************************/
/* Name: MDIO_program.c                                                 */
/* Author: Ahmed Yasser                                                 */
/* Version: V1.0                                                        */
/* Usage: This file contains logical implementations of UART Module     */
/************************************************************************/

/************************************************************************/
/*                              Includes                                */
/************************************************************************/
#include "MUART_interface.h"
#include "MUART_private.h"


/************************************************************************/
/*                          Functions' definitions                      */
/************************************************************************/

void muart_init(u16_t au16_baudRate)
{
	/*Disable double speed*/
	MUART_UCSRA= 0;	
	
	/*Enable Tx and Rx*/
	MUART_UCSRB= 0x18;
	
	/*Enable async mode, disabling parity,selecting one stop bit and using 8 bit*/
	MUART_UCSRC= 0x86;
	
	/*Setting the least significant baud rate*/
	MUART_UBRRL= (u8_t) au16_baudRate;
	
	/*Setting the most significant baud rate*/
	MUART_UBRRH= (u8_t) (au16_baudRate >>8);
	
	return;
}

void muart_sendByte(u8_t au8_dataByte)
{
	/*Checking if the UART data register is empty or not*/
	if (GET_BIT(MUART_UCSRA,5))
	{
		/*Setting the byte to send*/
		MUART_UDR= au8_dataByte;
		
		/*Wait until the transmission complete*/
		while(GET_BIT(MUART_UCSRA, 6)==0);
		
		/*Clearing the Txc bit*/
		SET_BIT(MUART_UCSRA,6);	
	}
	
	else
	{
		/*Do nothing*/
	}
	return;
}

void muart_recvByte(u8_t* pu8_dataByte)
{
	/*Check if the data is unread*/
	if (GET_BIT(MUART_UCSRA,7))
	{
		/*Getting the received data*/
		*pu8_dataByte= MUART_UDR;
	}
	return;
}

void muart_sendStream(u8_t* pu8_dataSream, u8_t au8_dataSize)
{
	/*Looping over data bytes*/
	while(au8_dataSize--)
	{
		if (GET_BIT(MUART_UCSRA,5))
		{
			/*Setting the byte to send*/
			MUART_UDR= *pu8_dataSream;
			
			/*Wait until the transmission complete*/
			while(GET_BIT(MUART_UCSRA, 6)==0);
			
			/*Clearing the Txc bit*/
			SET_BIT(MUART_UCSRA,6);
			
			/*Increasing pointer address for the next point/element*/
			pu8_dataSream++;
		}
		
		else
		{
			/*Do nothing*/
		}
	}
	
	return;
}
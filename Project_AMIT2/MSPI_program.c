/************************************************************************/
/* Name: MDIO_program.c                                                 */
/* Author: Ahmed Yasser                                                 */
/* Version: V1.0                                                        */
/* Usage: This file contains logical implementations of SPI Module      */
/************************************************************************/

/************************************************************************/
/*                              Includes                                */
/************************************************************************/
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_interface.h"
#include "MSPI_interface.h"

#define F_CPU 16000000UL
#include "util/delay.h"

/************************************************************************/
/*                           Important macros                           */
/************************************************************************/

#define TIMEOUT_VALUE		(50)

/************************************************************************/
/*                          Functions' definitions                      */
/************************************************************************/

void mspi_init(u8_t au8_spiDevType, u8_t au8_dataOrder, u8_t au8_dataTransfer_clkType, u8_t au8_clkFreq)
{
	/*Reset the control register*/
	MSPI_SPCR = 0;
	
	if((au8_clkFreq % 2)==0)
	{
		/*Enable double speed*/
		SET_BIT(MSPI_SPSR,0);
	}
	else
	{
		/*Disable double speed*/
		CLEAR_BIT(MSPI_SPSR,1);
	}
	
	/*Setting the control register parameters*/
	MSPI_SPCR = (1 << 6) | au8_spiDevType|au8_dataOrder|(au8_dataTransfer_clkType<<2) | (au8_clkFreq/2);
	
	return;
}

void mspi_masterSendRecv(u8_t au8_sendData, u8_t* au8_recvData)
{
	/*This variable used in timing out mechanism*/
	u8_t au8_timeOut=0;
	
	/*Set the master data*/
	MSPI_SPDR= au8_sendData;
	
	/*Wait until the SPI interrupt flag rises*/
	while(GET_BIT(MSPI_SPSR,7)==0 && (au8_timeOut < TIMEOUT_VALUE))
	{
		au8_timeOut++;
		
		/*wait for 1 microsecond*/
		_delay_us(1);
	}
	
	*au8_recvData= MSPI_SPDR;
	
	return;
}

void mspi_slaveSendRecv(u8_t au8_sendData, u8_t* au8_recvData)
{
	if(GET_BIT(MSPI_SPSR,7))
	{
		/*Get the received master data*/
		*au8_recvData=MSPI_SPDR;
		
		/*Set the new data*/
		MSPI_SPDR= au8_sendData;
	}
	else
	{
		/*Do nothing*/
	}
	
	return;
}
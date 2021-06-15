/************************************************************************/
/* Name: MDIO_interface.h                                               */
/* Author: Ahmed Yasser                                                 */
/* Version: V1.0                                                        */
/* Usage: This file contains interfacing information of SPI Module      */
/************************************************************************/


#ifndef MSPI_INTERFACE_H_
#define MSPI_INTERFACE_H_

#include "MSPI_private.h"
/************************************************************************/
/*                           Interfacing macros                         */
/************************************************************************/
/*Master and Slave selection*/
#define MSPI_MASTER_DEVICE		(0x10)
#define MSPI_SLAVE_DEVICE		(0x00)

/*SPI data order*/
#define MSPI_LSB_FIRST			(0x20)
#define MSPI_MSB_FIRST			(0x00)

/*Clock type in data transfer*/
#define MSPI_SAMPLE_R_SETUP_F	(0)
#define MSPI_SETUP_R_SAMPLE_F	(1)
#define MSPI_SAMPLE_F_SETUP_R	(2)
#define MSPI_SETUP_F_SAMPLE_R	(3)

/*SPI Clock*/
#define MSPI_CLK_PRE_2			(0)
#define MSPI_CLK_PRE_4			(1)
#define MSPI_CLK_PRE_8			(2)
#define MSPI_CLK_PRE_16			(3)
#define MSPI_CLK_PRE_32			(4)
#define MSPI_CLK_PRE_64			(5)
#define MSPI_CLK_PRE_128		(7)

/************************************************************************/
/*                           Functions' Prototype                       */
/************************************************************************/

/*Initializing the SPI module*/
void mspi_init(u8_t au8_spiDevType, u8_t au8_dataOrder, u8_t au8_dataTransfer_clkType, u8_t au8_clkFreq);

/*Master sends to and receives data from the slave*/
void mspi_masterSendRecv(u8_t au8_sendData, u8_t* au8_recvData);

/*Slave sends to and receives data from the slave*/
void mspi_slaveSendRecv(u8_t au8_sendData, u8_t* au8_recvData);

#endif /* MSPI_INTERFACE_H_ */
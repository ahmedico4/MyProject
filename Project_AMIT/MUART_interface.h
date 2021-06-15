/************************************************************************/
/* Name: MDIO_interface.h                                               */
/* Author: Ahmed Yasser                                                 */
/* Version: V1.0                                                        */
/* Usage: This file contains interfacing information of UART Module     */
/************************************************************************/
#include "LBIT_MATH.h"
#include "LSTD_TYPES.h"

#ifndef MUART_INTERFACE_H_
#define MUART_INTERFACE_H_

/************************************************************************/
/*                           Interfacing macros                         */
/************************************************************************/

/*Baud rate*/
#define MUART_2400_BR		(416)
#define MUART_4800_BR		(207)
#define MUART_9600_BR		(103)
#define MUART_19200_BR		(51)
#define MUART_115200_BR		(8)

/************************************************************************/
/*                           Functions' prototypes                      */
/************************************************************************/

/*This function is used to initialize UART peripheral with a specific baud rate*/
void muart_init(u16_t au16_baudRate);

/*Sending one byte*/
void muart_sendByte(u8_t au8_dataByte);

/*Receiving one byte*/
void muart_recvByte(u8_t* pu8_dataByte);

/*Sending many bytes of data*/
void muart_sendStream(u8_t* pu8_dataSream, u8_t au8_dataSize);


#endif /* MUART_INTERFACE_H_ */
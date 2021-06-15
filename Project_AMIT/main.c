/************************************************************************/
/* Name: Project_AMIT.c                                                 */
/* Author: Ahmed Yasser                                                 */
/* Version: V1.0                                                        */
/* Usage: This file contains logical implementations of the Project     */
/************************************************************************/

/************************************************************************/
/*                              Includes                                */
/************************************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_interface.h"
#include "MUART_interface.h"
#include "MSPI_interface.h"

#define F_CPU 16000000UL
#include "util/delay.h"

int main(void)
{
	/*Initializing two local variables x for UART and y for SPI*/
	u8_t x;
	u8_t y;
	
	/*Setting pins for the SPI*/
	mdio_setPinStatus(PORTA,PIN0,OUTPUT);
	mdio_setPinStatus(PORTB,PIN5|PIN7,OUTPUT);
	mdio_setPinStatus(PORTB,PIN6,INPUT_FLOAT);
	
	/*Send and Receive pins(Virtual Terminal)*/
	mdio_setPinStatus(PORTD, PIN0, INPUT_FLOAT);
	mdio_setPinStatus(PORTD, PIN1, OUTPUT);
	
	/*Just to check the above two lines is working*/
	mdio_setPinStatus(PORTC, PIN2, OUTPUT);
	
	/*Initializing the UART communication*/
	muart_init(MUART_9600_BR);
	
	/*Initializing the SPI as a Master device*/
	mspi_init(MSPI_MASTER_DEVICE,MSPI_MSB_FIRST,MSPI_SAMPLE_R_SETUP_F,MSPI_CLK_PRE_64);
	muart_recvByte(&x);
	
    while (1) 
    {
		muart_recvByte(&x);
		
		/*Setting it to LOW for to act as a SS pin*/
		mdio_setPinValue(PORTA,PIN0,LOW);
		
		/*When 'n' is sent, send 3 through the SPI to MCU2*/
		if( x == 'n')
		{
			mdio_setPinValue(PORTC,PIN2,HIGH);
			mspi_masterSendRecv(3, &y);
			_delay_ms(250);
			mdio_setPinValue(PORTA,PIN0,HIGH);
		}
		
		/*When 'f' is sent, send 4 through the SPI to MCU2*/
		else if(x == 'f')
		{
			mdio_setPinValue(PORTC,PIN2,LOW);
			mspi_masterSendRecv(4, &y);
			_delay_ms(250);
			mdio_setPinValue(PORTA,PIN0,HIGH);
		}
		
    }
}
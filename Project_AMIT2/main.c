/************************************************************************/
/* Name: Project_AMIT2.c                                                */
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
#include "MSPI_interface.h"

#define F_CPU 16000000UL
#include "util/delay.h"

/************************************************************************/
/*                        Code Implementation                           */
/************************************************************************/
int main(void)
{
	/*Initializing a local variable*/
	u8_t x;
	
	/*Setting pins for the SPI*/
	mdio_setPinStatus(PORTB,PIN4|PIN5|PIN7,OUTPUT);
	mdio_setPinStatus(PORTB,PIN6,INPUT_FLOAT);
	
	/*Setting pins for the LED*/
	mdio_setPinStatus(PORTD,PIN3,OUTPUT);
	mdio_setPinStatus(PORTC,PIN2,OUTPUT);
	
	/*Initializing the SPI as a slave device*/
	mspi_init(MSPI_SLAVE_DEVICE,MSPI_MSB_FIRST,MSPI_SAMPLE_R_SETUP_F,MSPI_CLK_PRE_64);
	
   while(1)
   {
	   mspi_slaveSendRecv(3, &x);

	   /*Actuator 2 is ON*/
	   if(x== 3)
	   {
		   mdio_setPinValue(PORTD,PIN3,HIGH);
		   mdio_setPinValue(PORTC,PIN2,LOW);
	   }
	   
	   /*Actuator 1 is ON*/
	   else if(x== 4)
	   {
		   mdio_setPinValue(PORTC,PIN2,HIGH);
		   mdio_setPinValue(PORTD,PIN3,LOW);
	   }
   }
}
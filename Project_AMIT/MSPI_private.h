/************************************************************************/
/* Name: MDIO_private.h                                                 */
/* Author: Ahmed Yasser                                                 */
/* Version: V1.0                                                        */
/* Usage: This file contains private information of SPI Module          */
/************************************************************************/

#ifndef MSPI_PRIVATE_H_
#define MSPI_PRIVATE_H_

/************************************************************************/
/*                            SPI Registers                             */
/************************************************************************/

#define MSPI_SPCR    (*(volatile u8_t *)(0x2D))
#define MSPI_SPSR    (*(volatile u8_t *)(0x2E))
#define MSPI_SPDR    (*(volatile u8_t *)(0x2F))


#endif /* MSPI_PRIVATE_H_ */
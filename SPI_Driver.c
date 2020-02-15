/*
 ============================================================================
 Name        : SPI_Driver.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


#include "SPI_Driver.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void SPI_initMaster(void)
{
	/******** Configure SPI Master Pins *********
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output
	 * MISO(PB6) --> Input
	 * SCK(PB7) --> Output
	 ********************************************/
	gpioPinDirection(GPIOB,BIT4,OUTPUT);
	gpioPinDirection(GPIOB,BIT5,OUTPUT);
	gpioPinDirection(GPIOB,BIT6,INPUT);
	gpioPinDirection(GPIOB,BIT7,OUTPUT);


	SPCR = (1<<SPE) | (1<<MSTR); // enable SPI + enable Master + choose SPI clock = Fosc/4
}

void SPI_initSlave(void)
{
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/
	gpioPinDirection(GPIOB,BIT4,INPUT);
	gpioPinDirection(GPIOB,BIT5,INPUT);
	gpioPinDirection(GPIOB,BIT6,OUTPUT);
	gpioPinDirection(GPIOB,BIT7,INPUT);
	SPCR = (1<<SPE); // just enable SPI + choose SPI clock = Fosc/4
}

void SPI_sendByte(const uint8_t data)
{
	SPDR = data; //send data by SPI
	while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data is sent correctly)
}

uint8_t SPI_recieveByte(void)
{
   while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1(data is receive correctly)
   return SPDR; //return the received byte from SPI data register
}

void SPI_SendString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		SPI_sendByte(Str[i]);
		i++;
	}
}

void SPI_ReceiveString(char *Str)
{
	unsigned char i = 0;
	Str[i] = SPI_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = SPI_recieveByte();
	}
	Str[i] = '\0';
}

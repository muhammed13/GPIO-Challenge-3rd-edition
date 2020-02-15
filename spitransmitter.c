/*
 * main.c
 *
 * Created: 2/10/2020 11:31:55 PM
 *  Author: hazem
 */ 

#include "SPI_Driver.h"
#include "softwareDelay.h"

void SPI_sender_test(void)
{
	SPI_initMaster();
	gpioPinDirection(GPIOC,BIT4,INPUT);
    while(1)
    {
		if(gpioPinRead(GPIOC,BIT4)) //if switch is pressed
		{
			SPI_sendByte(1);
		}
		else
		{
			SPI_sendByte(0);
		}
    }

}


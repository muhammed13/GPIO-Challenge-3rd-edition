
#include "SPI_Driver.h"
#include "softwareDelay.h"
#include "sevenSeg.h"

void SPI_receiver_func(void)
{
	uint8_t data_received;
	SPI_initSlave();
	gpioPinDirection(GPIOB,BIT3,OUTPUT);
    while(1)
    {
		data_received = SPI_recieveByte(); //receive data from the master Micro-controller
		if(data_received == 1)
		{
			gpioPinWrite(GPIOB,BIT3,HIGH);
		}
		else if(data_received == 0)
		{
			gpioPinWrite(GPIOB,BIT3,LOW);
		}
    }
}

/*#include "SPI_Driver.h"
#include "softwareDelay.h"
#include "sevenSeg.h"

void SPI_receiver_func(void)
{
	SPI_initSlave();
	sevenSegInit(SEG_0);
	sevenSegInit(SEG_1);
	gpioPinDirection(GPIOB,BIT3,OUTPUT);
	uint8_t data=0;

	while(1)
	{

		if(SPI_recieveByte()==20)
		{
			sevenSegWrite(SEG_0,data);
			sevenSegEnable(SEG_0);
			sevenSegDisable(SEG_1);
			data++;
			softwareDelayMs(1000);

			if(data==9)
			{
				data=0;
			}
			gpioPinWrite(GPIOB,BIT3,LOW);
		}
		else
		{
			gpioPinWrite(GPIOB,BIT3,BIT3);
		}

		
		
	}
	

}
*/

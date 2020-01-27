#include "sevenSeg.h"

void sevenSegInit(En_SevenSegId_t a_segment_id)
{
	switch (a_segment_id)
	{
	case SEG_0:
		gpioPinDirection(SEG_BCD_GPIO,SEG_BCD_BITS,OUTPUT);
		gpioPinWrite(SEG_BCD_GPIO, SEG_BCD_BITS, SEG_BCD_BITS);
		gpioPinDirection(SEG_EN1_GPIO, SEG_EN1_BIT,OUTPUT);
		gpioPinWrite(SEG_EN1_GPIO, SEG_EN1_BIT, SEG_EN1_BIT);
		break;
	case SEG_1:
		gpioPinDirection(SEG_BCD_GPIO, SEG_BCD_BITS,OUTPUT);
		gpioPinWrite(SEG_BCD_GPIO, SEG_BCD_BITS, SEG_BCD_BITS);
		gpioPinDirection(SEG_EN2_GPIO, SEG_EN2_BIT,OUTPUT);
		gpioPinWrite(SEG_EN2_GPIO, SEG_EN2_BIT, SEG_EN2_BIT);
		break;
	}
}


void sevenSegEnable(En_SevenSegId_t en_segment_id)
{
	switch (en_segment_id)
	{
	case SEG_0:
		gpioPinWrite(SEG_EN1_GPIO, SEG_EN1_BIT, SEG_EN1_BIT);
		break;
	case SEG_1:
		gpioPinWrite(SEG_EN2_GPIO, SEG_EN2_BIT, SEG_EN2_BIT);
		break;
	}
}

void sevenSegDisable(En_SevenSegId_t en_segment_id)
{
	switch (en_segment_id)
	{
	case SEG_0:
		gpioPinWrite(SEG_EN1_GPIO, SEG_EN1_BIT, LOW);
		/*here I send LOW as a value because it will be ORed by the way
		 * with the port value in "gpioPinWrite" function
		 */
		break;
	case SEG_1:
		gpioPinWrite(SEG_EN2_GPIO, SEG_EN2_BIT, LOW);
		break;
	}
}

void sevenSegWrite(En_SevenSegId_t en_segment_id, uint8_t u8_number)
{
	switch (en_segment_id)
	{
	case SEG_0:
		gpioPinWrite(SEG_BCD_GPIO, SEG_BCD_BITS, LOW);
		gpioPinWrite(SEG_BCD_GPIO, SEG_BCD_BITS, u8_number);
		break;
	case SEG_1:
		gpioPinWrite(SEG_BCD_GPIO, SEG_BCD_BITS, LOW);
		gpioPinWrite(SEG_BCD_GPIO, SEG_BCD_BITS, u8_number);
		break;
	}
}

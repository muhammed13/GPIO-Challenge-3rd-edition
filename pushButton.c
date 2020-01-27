#include "pushButton.h"
void pushButtonInit(En_buttonId_t en_butotn_id)
{
	switch(en_butotn_id)
	{
		case BTN_0:
			gpioPinDirection(BTN_0_GPIO, BTN_0_BIT, INPUT);
			break;
		case BTN_1:
			gpioPinDirection(BTN_1_GPIO, BTN_1_BIT, INPUT);
			break;
		case BTN_2:
			gpioPinDirection(BTN_2_GPIO, BTN_2_BIT, INPUT);
			break;
		case BTN_3:
			gpioPinDirection(BTN_3_GPIO, BTN_3_BIT, INPUT);
			break;
		case BTN_4_INT0:
			gpioPinDirection(GPIOD, BIT2, INPUT);
			break;
	}
}

En_buttonStatus_t pushButtonGetStatus(En_buttonId_t en_butotn_id)
{
	unsigned char current_status=0;
	switch(en_butotn_id)
	{
		case BTN_0:
			if(gpioPinRead(BTN_0_GPIO, BTN_0_BIT))
			{
				softwareDelayMs(30);
				/*second check due to switch de-bouncing*/
				if(gpioPinRead(BTN_0_GPIO, BTN_0_BIT))
				{
					current_status=gpioPinRead(BTN_0_GPIO, BTN_0_BIT);
				}
			}
			break;

		case BTN_1:
			if(gpioPinRead(BTN_1_GPIO, BTN_1_BIT))
			{
				softwareDelayMs(30);
				/*second check due to switch de-bouncing*/
				if(gpioPinRead(BTN_1_GPIO, BTN_1_BIT))
				{
					current_status=gpioPinRead(BTN_1_GPIO, BTN_1_BIT);
				}
			}
			break;

		case BTN_2:
			if(gpioPinRead(BTN_2_GPIO, BTN_2_BIT))
			{
				softwareDelayMs(30);
				/*second check due to switch de-bouncing*/
				if(gpioPinRead(BTN_2_GPIO, BTN_2_BIT))
				{
					current_status=gpioPinRead(BTN_2_GPIO, BTN_2_BIT);
				}
			}
			break;

		case BTN_3:
			if(gpioPinRead(BTN_3_GPIO, BTN_3_BIT))
			{
				softwareDelayMs(30);
				/*second check due to switch de-bouncing*/
				if(gpioPinRead(BTN_3_GPIO, BTN_3_BIT))
				{
					current_status=gpioPinRead(BTN_3_GPIO, BTN_3_BIT);
				}
			}
			break;

		case BTN_4_INT0:
			if(gpioPinRead(GPIOD, BIT2))
			{
				softwareDelayMs(30);
				/*second check due to switch de-bouncing*/
				if(gpioPinRead(GPIOD, BIT2))
				{
					current_status=gpioPinRead(GPIOD, BIT2);
				}
			}
			break;

	}
	return current_status;
}

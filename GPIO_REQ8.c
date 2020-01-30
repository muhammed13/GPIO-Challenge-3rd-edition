#include "GPIO_REQ8.h"
#define NUMBER_OF_ITERATION_FOR_ONE_SEC 80000
#define MIN_FLAG_VALUE 10
#define START 0

void button_led(void)
{
	uint8_t u8_flag=START;
	uint32_t u32_i;
	Led_Init(LED_1);
	pushButtonInit(BTN_1);
	while(TRUE)
	{
		if(pushButtonGetStatus(BTN_1))
		{
			Led_On(LED_1);
	    	for(u32_i=START;u32_i<NUMBER_OF_ITERATION_FOR_ONE_SEC;u32_i++)
	    	{
	    		if(pushButtonGetStatus(BTN_1))
	    		{
	    			u8_flag++;
	    		}
	    	}
	    	if(u8_flag>MIN_FLAG_VALUE)
	    	{
	    		softwareDelayMs(ONE_SEC);
	    	}
	    	Led_Off(LED_1);
	    	softwareDelayMs(ONE_SEC);
	    	u8_flag=START;
		}
	}
}


void button_led_using_timer0(void)
{
	uint8_t u8_flag=START;
	uint32_t u32_i;
	Led_Init(LED_1);
	pushButtonInit(BTN_1);
	while(TRUE)
	{
		if(pushButtonGetStatus(BTN_1))
		{
			Led_On(LED_1);
	    	for(u32_i=START;u32_i<NUMBER_OF_ITERATION_FOR_ONE_SEC;u32_i++)
	    	{
	    		if(pushButtonGetStatus(BTN_1))
	    		{
	    			u8_flag++;
	    		}
	    	}
	    	if(u8_flag>MIN_FLAG_VALUE)
	    	{
	    		timer0DelayMs(ONE_SEC);
	    	}
	    	Led_Off(LED_1);
	    	timer0DelayMs(ONE_SEC);
	    	u8_flag=START;
		}
	}
}

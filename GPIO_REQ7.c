#include "GPIO_REQ7.h"

#define MAX_NUMBER 9
#define SWITCHING_TIME 5
#define NUMBER_OF_ITERATION_FOR_ONE_SEC 50

void sevensegments(void)
{
	sevenSegInit(SEG_0);
	sevenSegInit(SEG_1);

	uint8_t counter1;
	uint8_t counter2=START_;
	uint8_t i;
	while(TRUE)
	{
		for(counter1=START_;counter1<=MAX_NUMBER;counter1++)
		{
			for(i=START_;i<NUMBER_OF_ITERATION_FOR_ONE_SEC;i++)
			{
				sevenSegWrite(SEG_0, counter1);
				sevenSegEnable(SEG_0);
				softwareDelayMs(SWITCHING_TIME);
				sevenSegDisable(SEG_0);
				softwareDelayMs(SWITCHING_TIME);

				sevenSegWrite(SEG_1, counter2);
				sevenSegEnable(SEG_1);
				softwareDelayMs(SWITCHING_TIME);
				sevenSegDisable(SEG_1);
				softwareDelayMs(SWITCHING_TIME);

			}
		}
		counter2++;
		if(counter2==MAX_NUMBER+1)
		{
			counter2=START_;
		}
	}
}



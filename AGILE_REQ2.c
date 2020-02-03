/*
 ============================================================================
 Name        : AGILE_REQ2.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#include "AGILE_REQ2.h"


void ultrasonic_sensor_start(void)
{
	uint8_t u8_obstacle_distance;
	gpioPinDirection(GPIOB,LED_0_BIT | LED_1_BIT | LED_2_BIT | LED_3_BIT,
			                    LED_0_BIT | LED_1_BIT | LED_2_BIT | LED_3_BIT);
	US_init();
	while(1)
	{
		US_triger();
		US_start();
		u8_obstacle_distance=US_get_reading();
		US_stop();
		gpioPinWrite(LED_0_GPIO,LED_0_BIT | LED_1_BIT | LED_2_BIT | LED_3_BIT,
				     u8_obstacle_distance);
		softwareDelayMs(1000);
	}
}

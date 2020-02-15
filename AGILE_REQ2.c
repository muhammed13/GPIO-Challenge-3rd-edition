/*
 ============================================================================
 Name        : AGILE_REQ2.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#include "AGILE_REQ2.h"


uint8_t g8_global_distance;
void ultrasonic_sensor_start(void)
{
	uint8_t u8_obstacle_distance;
	gpioPinDirection(GPIOB,LED_0_BIT | LED_1_BIT | LED_2_BIT | LED_3_BIT,
			                    LED_0_BIT | LED_1_BIT | LED_2_BIT | LED_3_BIT);
	//gpioPortDirection(1,OUTPUT);
	US_init();
	while(1)
	{
		US_triger();
		//US_start();
		u8_obstacle_distance=US_get_reading();
		//TCNT1=g8_global_distance;
		US_stop();
		gpioPinWrite(LED_0_GPIO,LED_0_BIT | LED_1_BIT | LED_2_BIT | LED_3_BIT,
				g8_global_distance);
		//gpioPortWrite(1,u8_obstacle_distance);
		//softwareDelayMs(1000);
	}
}

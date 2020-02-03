/*
 ============================================================================
 Name        : AGILE_REQ4.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

/*********************************includes**********************************/
#include "AGILE_REQ4.h"
/***************************************************************************/


/*********************************definitions*******************************/

/***************************************************************************/


/******************************global variables*****************************/


/***************************************************************************/


/******************************static functions*****************************/

/***************************************************************************/


void car_with_ultrasonic(void)
{
	sei();
	g8_gloabal_car_duty=80;
	uint8_t u8_obstacle_distance;
	uint8_t u8_k;
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	MotorDC_Dir(MOT_1,FORWARD);
	MotorDC_Dir(MOT_2,FORWARD);


	gpioPinDirection(LED_0_GPIO,LED_0_BIT | LED_1_BIT | LED_2_BIT | LED_3_BIT,
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
		if(u8_obstacle_distance<=50 && u8_obstacle_distance>30)
		{
			MotorDC_Dir(MOT_1,FORWARD);
			MotorDC_Dir(MOT_2,FORWARD);
			MotorDC_Speed_HwPWM(50);
		}
		else if(u8_obstacle_distance==30)
		{
			MotorDC_Dir(MOT_1,STOP);
			MotorDC_Dir(MOT_2,STOP);
			softwareDelayMs(500);
			for(u8_k=0;u8_k<1;u8_k++)     /*turn right*/
			{
				MotorDC_Dir(MOT_1,FORWARD);
				MotorDC_Speed_HwPWM(80);
				softwareDelayMs(1000);
			}
			g8_gloabal_car_duty=80;
		}
		else if(u8_obstacle_distance<30)
		{
			MotorDC_Dir(MOT_1,STOP);
			MotorDC_Dir(MOT_2,STOP);
			softwareDelayMs(500);
			MotorDC_Speed_HwPWM(50);
			MotorDC_Dir(MOT_1,BACKWARD);
			MotorDC_Dir(MOT_2,BACKWARD);
		}
		else                           /*distance is greater than 50cm*/
		{
			MotorDC_Dir(MOT_1,FORWARD);
			MotorDC_Dir(MOT_2,FORWARD);
			MotorDC_Speed_HwPWM(80);
		}
	}
}


/*
 ============================================================================
 Name        : AGILE_REQ3.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#include "AGILE_REQ3.h"

#define NUMBER_OF_ITERATION_FOR_ONE_SEC 80000

uint8_t g8_gloabal_car_duty;
void car_application_with_phase_correct(void)
{
	sei();
	g8_gloabal_car_duty=0;
	uint8_t u8_i;
	uint8_t u8_j;
	uint8_t u8_k;
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	MotorDC_Dir(MOT_1,FORWARD);
	MotorDC_Dir(MOT_2,FORWARD);



	for(u8_i=0;u8_i<10;u8_i++)
	{
		MotorDC_Speed_HwPWM(g8_gloabal_car_duty);
		softwareDelayMs(500);
		g8_gloabal_car_duty+=10;
	}

	g8_gloabal_car_duty=100;
	for(u8_j=0;u8_j<10;u8_j++)
	{
		MotorDC_Speed_HwPWM(g8_gloabal_car_duty);
		softwareDelayMs(500);
		g8_gloabal_car_duty-=10;
	}

	MotorDC_Dir(MOT_1,STOP);
	MotorDC_Dir(MOT_2,STOP);
	softwareDelayMs(500);
	g8_gloabal_car_duty=80;
	for(u8_k=0;u8_k<1;u8_k++)
	{
		MotorDC_Dir(MOT_1,FORWARD);
		MotorDC_Speed_HwPWM(g8_gloabal_car_duty);
		softwareDelayMs(1000);
	}
	MotorDC_Dir(MOT_1,STOP);
	timer0Stop();

}

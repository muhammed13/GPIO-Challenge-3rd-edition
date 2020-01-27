/*
 ============================================================================
 Name        : GPIO_REQ15.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */
#include "GPIO_REQ15.h"

#define NUMBER_OF_ITERATION_FOR_ONE_SEC 80000

uint8_t g8_gloabal_car_duty;
void car_application(void)
{
	sei();
	g8_gloabal_car_duty=0; /*100 instead of 0 because the duty cycle inverted in ISR*/
	uint8_t u8_i;
	uint8_t u8_j;
	uint8_t u8_k;
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	MotorDC_Dir(MOT_1,FORWARD);
	MotorDC_Dir(MOT_2,FORWARD);

	//gpioPinWrite(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,MOTOR_OUT_2B_BIT);

	for(u8_i=0;u8_i<5;u8_i++)
	{
		MotorDC_Speed_PollingWithT0(g8_gloabal_car_duty);
		softwareDelayMs(1000);       /*1sec on simulation*/
		g8_gloabal_car_duty+=20;
	}

	for(u8_j=0;u8_j<5;u8_j++)
	{
		MotorDC_Speed_PollingWithT0(g8_gloabal_car_duty);
		softwareDelayMs(1000);
		g8_gloabal_car_duty-=20;
	}

	g8_gloabal_car_duty=50;
	for(u8_k=0;u8_k<1;u8_k++)
	{
		MotorDC_Dir(MOT_1,STOP);
		MotorDC_Speed_PollingWithT0(g8_gloabal_car_duty);
		softwareDelayMs(1000);
	}
	MotorDC_Dir(MOT_1,STOP);
	MotorDC_Dir(MOT_2,STOP);
	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_NO_CLOCK,6,0,T0_INTERRUPT_NORMAL);
}


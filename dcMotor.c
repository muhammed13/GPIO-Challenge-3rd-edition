/*
 ============================================================================
 Name        : dcMotor.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#include "dcMotor.h"



void MotorDC_Init(En_motorType_t en_motor_number)
{
	switch(en_motor_number)
	{
		case(MOT_1):
				gpioPinDirection(MOTOR_OUT_1A_GPIO,MOTOR_EN_1_BIT,OUTPUT);  /*set direction for motor1 enable pin*/

				gpioPinWrite(MOTOR_OUT_1A_GPIO,MOTOR_EN_1_BIT,LOW);

				gpioPinDirection(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,OUTPUT);

				gpioPinWrite(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);

				gpioPinDirection(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,OUTPUT);

				gpioPinWrite(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);

				break;

		case(MOT_2):
				gpioPinDirection(MOTOR_OUT_2A_GPIO,MOTOR_EN_2_BIT,OUTPUT);  /*set direction for motor1 enable pin*/

				gpioPinWrite(MOTOR_OUT_2A_GPIO,MOTOR_EN_2_BIT,LOW);   /*disable motor1*/

				gpioPinDirection(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,OUTPUT);

				gpioPinWrite(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);

				gpioPinDirection(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,OUTPUT);

				gpioPinWrite(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);

				break;
	}
}


void MotorDC_Dir(En_motorType_t en_motor_number, En_motorDir_t en_motor_dir)
{
	switch(en_motor_number)
	{
		case(MOT_1):
				switch(en_motor_dir)
				{
				case(STOP):
						gpioPinWrite(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
						gpioPinWrite(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);

						break;
				case(FORWARD):
						gpioPinWrite(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
						gpioPinWrite(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,MOTOR_OUT_1B_BIT);
						break;
				case(BACKWARD):
						gpioPinWrite(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,MOTOR_OUT_1A_BIT);
						gpioPinWrite(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
						break;
				}

				break;

		case(MOT_2):
				switch(en_motor_dir)
				{
				case(STOP):
						gpioPinWrite(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
						gpioPinWrite(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
						break;
				case(FORWARD):
						gpioPinWrite(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
						gpioPinWrite(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,MOTOR_OUT_2B_BIT);
						break;
				case(BACKWARD):
						gpioPinWrite(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,MOTOR_OUT_2A_BIT);
						gpioPinWrite(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
						break;
				}
	}
}


void MotorDC_Speed_PollingWithT0(uint8_t u8_motor_speed)
{
	timer0SwPWM(u8_motor_speed,T0_SW_FREQUENCY_61HZ);
}


void MotorDC_Speed_HwPWM(uint8_t u8_motor_speed)
{
	timer1HwPWM_PhaseCorrect(u8_motor_speed,T1_PHASE_CORRECT_FREQUENCY_400HZ);
}

#include "GPIO_REQ8.h"
#include "GPIO_REQ7.h"
#include "GPIO_REQ9.h"
#include "GPIO_REQ15.h"
#include "timers.h"
#include "softwareDelay.h"
#include "interrupt.h"
#include "ISRs.h"
#include "led.h"
#include "AGILE_REQ2.h"
#include "AGILE_REQ3.h"

int main(void)
{
	/*REQ7*/
	/*sevensegments();*/

	/*REQ8*/
	/*button_led();*/

	/*REQ9*/
	/*trafficlight();*/

	/*REQ10*/
	/*trafficlight_using_timer0();*/
	/*trafficlight_using_timer1();*/
	/*button_led_using_timer0();*/

	/*REQ12 -- */
	/*trafficlight_using_timer0_using_interrupts();*/

/*you have to enable the specified ISR for REQ12 & REQ13*/

	/*REQ13*/
	/*trafficlight_using_timer0_using_interrupts_button();*/


	/*REQ14*/
	/********timer0 software fast pwm test***********/
/*
	sei();
	gpioPinDirection(GPIOB, BIT3, OUTPUT);
	gpioPinWrite(GPIOB, BIT3,LOW);

	for(int i=0;i<6;i++)
	{
	timer0SwPWM(i*20,100);
	softwareDelayMs(1000);
	}
*/
/************ timer0 software fast pwm test********************/
/*
	gpioPinDirection(GPIOD, BIT3, OUTPUT);
	gpioPinWrite(GPIOD, BIT3,LOW);
	timer0HwPWM(50,T0_FREQUENCY_61HZ);
*/

	/************ timer0 software phase correct pwm test********************/
/*
	gpioPinDirection(GPIOD, BIT3, OUTPUT);
	gpioPinWrite(GPIOD, BIT3,LOW);
	timer0HwPWM_PhaseCorrect(50,T0_PHASE_CORRECT_FREQUENCY_122HZ);
*/

	/*timer0 pwm using normal mode*/
	/*
	sei();
	gpioPinDirection(GPIOB, BIT7, OUTPUT);
	gpioPinWrite(GPIOB, BIT7,LOW);
	g8_gloabal_car_duty=70;        //this duty cycle is inverted
	//timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_NO,6,0,T0_INTERRUPT_NORMAL);

	//T0_PRESCALER_NO ==> 97HZ ... T0_PRESCALER_64 ==> 3.8HZ
*/
    /*******timer1 hardware fast pwm test************/
/*
	gpioPinDirection(GPIOD, BIT5, OUTPUT);
	gpioPinWrite(GPIOD, BIT5,LOW);
	timer1HwPWM(50,T1_FREQUENCY_100HZ);
*/

    /*******timer1 hardware phase corret pwm test************/
/*
	gpioPinDirection(GPIOD, BIT5, OUTPUT);
	gpioPinWrite(GPIOD, BIT5,LOW);
	timer1HwPWM_PhaseCorrect(50,T1_PHASE_CORRECT_FREQUENCY_400HZ);
*/

	/*REQ15*/
	/*
	sei();
	Led_Init(LED_0);
	Led_On(LED_0);
	MotorDC_Speed_PollingWithT0(50);
	*/

	/*timer0 swpwm test*/
/*
	sei();
	gpioPinDirection(GPIOB, BIT3, OUTPUT);
	gpioPinWrite(GPIOB, BIT3,LOW);
	timer0SwPWM(50,T0_FREQUENCY_61HZ);
*/
	/*first car application test*/
	/*I have to apply the ISR*/
	/*car_application();*/

	/*US test*/
	ultrasonic_sensor_start();

	/***car application phase correct test***/
	/*car_application_with_phase_correct();*/
/*
	while(1)
	{
		INT0_Init(3);
		if(g8_gloabal_int0_flag==1)
		{
			gpioPinDirection(GPIOB, BIT0, OUTPUT);
			gpioPinWrite(GPIOB, BIT0,BIT0);
			g8_gloabal_int0_flag=0;
			softwareDelayMs(1000);
		}
		else
		{
			gpioPinDirection(GPIOB, BIT0, OUTPUT);
			gpioPinWrite(GPIOB, BIT0,LOW);
			softwareDelayMs(1000);
		}
	}

*/
	while(1)
	{

	}
	return 0;

}

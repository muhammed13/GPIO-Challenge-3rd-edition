#include "GPIO_REQ8.h"
#include "GPIO_REQ7.h"
#include "GPIO_REQ9.h"
#include "GPIO_REQ15.h"
#include "timers.h"
#include "softwareDelay.h"
#include "interrupt.h"
#include "led.h"
//uint8_t g8_gloabal_car_duty;

int main()
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
	/*
	sei();
	trafficlight_using_timer0_using_interrupts();
*/

	/*REQ13*/
/*
	INT0_Init();
	trafficlight_using_timer0_using_interrupts_button();
*/

	/*REQ14*/
	/********timer0 fast pwm test***********/
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
	/*timer0 pwm using normal mode*/
	/*
	sei();
	gpioPinDirection(GPIOB, BIT7, OUTPUT);
	gpioPinWrite(GPIOB, BIT7,LOW);
	g8_gloabal_car_duty=70;        /*this duty cycle is inverted*/
	//timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_NO,6,0,T0_INTERRUPT_NORMAL);

	/*T0_PRESCALER_NO ==> 97HZ ... T0_PRESCALER_64 ==> 3.8HZ */

    /*******timer1 pwm test************/
/*
	gpioPinDirection(GPIOD, BIT5, OUTPUT);
	gpioPinWrite(GPIOD, BIT5,LOW);
	timer1SwPWM(50,T1_FREQUENCY_25HZ);
*/
	/***interrupt test**/
/*
	INT0_Init();
	gpioPinDirection(GPIOB,BIT1,OUTPUT);
	gpioPinWrite(GPIOB,BIT1,LOW);
*/

/*
	gpioPinDirection(GPIOD, BIT5, OUTPUT);
	gpioPinWrite(GPIOD, BIT5,LOW);
	car_application();
*/

	/*REQ15*/
	/*
	sei();
	Led_Init(LED_0);
	Led_On(LED_0);
	MotorDC_Speed_PollingWithT0(50);
	*/
	while(1)
	{
		car_application();

	}
	return 0;

}

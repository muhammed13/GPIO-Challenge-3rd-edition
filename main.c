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
#include "UART.h"
#include "UART_Sender.h"
#include "UART_Receiver.h"
#include "UART_SPI_ApplicationMicro1.h"
#include "UART_SPI_ApplicationMicro2.h"
#include "SPI_Driver.h"

#define NULL_PTR ((void*)0)
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
	//ultrasonic_sensor_start();


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

	/*
	gpioPinDirection(GPIOD,BIT2,INPUT);
	gpioPinDirection(GPIOA,BIT0,OUTPUT);
	INT0_Init(3);
	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,0,T0_POLLING);
	while(1)
	{
		gpioPinWrite(US_TRIGGER_GPIO,US_TRIGGER_BIT,US_TRIGGER_BIT);
		softwareDelayMs(1);
		gpioPinWrite(US_TRIGGER_GPIO,US_TRIGGER_BIT,LOW);
		softwareDelayMs(1);
	}
	*/


	/*******************UART test***************************/
	/*
	UART_Config_Structure uart_initialization_structure;

	uart_initialization_structure.Char_Size=USART_8_Bit_CHAR;
	uart_initialization_structure.Clk_Polarity_Mode=TX_RISING_RX_FALLING;
	uart_initialization_structure.Speed_Mode=USART_DOUBLE_SPEED;
	uart_initialization_structure.Parity_Mode=USART_NO_PARITY;
	uart_initialization_structure.Stop_Bit_Mode=USART_1_STOPBIT;
	uart_initialization_structure.Receive_Mode=USART_RECIEVE_ENABLE;
	uart_initialization_structure.Transmit_Mode=USART_TRANSMIT_ENABLE;
	uart_initialization_structure.Double_Speed_Baud_Rate=BAUD9600;


	UART_init(&uart_initialization_structure);
	uint8_t Str[20];
	uint8_t data;
	while(1)
	{
		data = UART_recieveByte(); //Receive Byte from Terminal1
		UART_sendByte(data); //Resend the received byte to Terminal2
	}
	*/


	/*************receiver************************/
/*
	gpioPortDirection(GPIOB,OUTPUT);
	gpioPortWrite(GPIOB,LOW);
	uint8_t num=0;

	UART_Config_Structure uart_initialization_structure;

	uart_initialization_structure.Char_Size=USART_8_Bit_CHAR;
	uart_initialization_structure.Clk_Polarity_Mode=TX_RISING_RX_FALLING;
	uart_initialization_structure.Speed_Mode=USART_DOUBLE_SPEED;
	uart_initialization_structure.Parity_Mode=USART_NO_PARITY;
	uart_initialization_structure.Stop_Bit_Mode=USART_1_STOPBIT;
	uart_initialization_structure.Receive_Mode=USART_RECIEVE_ENABLE;
	uart_initialization_structure.Transmit_Mode=USART_TRANSMIT_ENABLE;
	uart_initialization_structure.Double_Speed_Baud_Rate=BAUD9600;


	UART_init(&uart_initialization_structure);
	while(1)
	{
		num=UART_recieveByte();
		gpioPortWrite(GPIOB,(num<<4));
		softwareDelayMs(500);

	}
*/


	/**************sender*****************************/

	/*
	uint8_t num=0;
	UART_Config_Structure uart_initialization_structure;

	uart_initialization_structure.Char_Size=USART_8_Bit_CHAR;
	uart_initialization_structure.Clk_Polarity_Mode=TX_RISING_RX_FALLING;
	uart_initialization_structure.Speed_Mode=USART_DOUBLE_SPEED;
	uart_initialization_structure.Parity_Mode=USART_NO_PARITY;
	uart_initialization_structure.Stop_Bit_Mode=USART_1_STOPBIT;
	uart_initialization_structure.Receive_Mode=USART_RECIEVE_ENABLE;
	uart_initialization_structure.Transmit_Mode=USART_TRANSMIT_ENABLE;
	uart_initialization_structure.Double_Speed_Baud_Rate=BAUD9600;


	UART_init(&uart_initialization_structure);
	softwareDelayMs(3000);
	while(1)
	{
		 UART_sendByte(num);
		num++;
		if(num==15)
		{
			num=0;
		}
		softwareDelayMs(500);
	}
*/

	/*UART test*/
	//UART_Sender_func();
	//UART_Receiver_func();


	/*SPI test*/
    //SPI_receiver_func();
	//SPI_sender_test();


	/*UART_SPI_APP_MICRO1*/
	//Micro_OneApplication();

	Micro_TwoApplication();


	return 0;

}

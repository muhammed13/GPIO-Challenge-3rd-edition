/*
 ============================================================================
 Name        : ISRs.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */
#include "ISRs.h"

#define NULL_PTR ((void*)0)


volatile uint8_t g8_gloabal_int0_flag=0;
volatile uint8_t u8_local_int0_flag=0;
volatile uint32_t timer0_compare_match_tickes=0;

/****************************this ISRs for testing************************/
/*
ISR(INT0_vect)
{
	//gpioPinDirection(GPIOB, BIT1, OUTPUT);
	//gpioPinToggle(GPIOB,BIT1);
	g8_gloabal_int0_flag=1;
}
*/
/***********************************************************************/

/****************this ISRs for state machine using interrupt*****************/
/*
ISR(TIMER0_COMP_vect)
{
	static uint16_t u16_timer_tick=0;
	if(u16_timer_tick==1000 || u8_local_int0_flag==1)
	{
		switch(g8_state)
		{
			case 1:
				Led_Off(LED_2);
				Led_Off(LED_3);
				Led_On(LED_1);
				g8_state=3;
				break;
			case 2:
				Led_Off(LED_1);
				Led_Off(LED_3);
				Led_On(LED_2);
				g8_state=1;
				break;
			case 3:
				Led_Off(LED_1);
				Led_Off(LED_2);
				Led_On(LED_3);
				g8_state=2;
				break;
		}
		u16_timer_tick=0;
	}
	u16_timer_tick++;
	u8_local_int0_flag=0;
}

ISR(INT2_vect)
{
	g8_gloabal_int0_flag=1;
	u8_local_int0_flag=1;
}
*/
/*****************************************************************************/


/****************************these ISRs for TIMER0 SWPWM****************************/
/*
ISR(TIMER0_OVF_vect)
{
	gpioPinWrite(GPIOD, BIT4,BIT4);
	gpioPinWrite(GPIOD, BIT5,BIT5);
	TCNT0=g8_TCNT0_value_Swpwm_ISR;
}

ISR(TIMER0_COMP_vect)
{
	gpioPinWrite(GPIOD, BIT4,LOW);
	gpioPinWrite(GPIOD, BIT5,LOW);
}
*/
/*****************************************************************************/


/*******************************these ISRs for Ultrasonic sensor*******************************************/

//ISR(INT0_vect)
//{
	//gpioPinDirection(GPIOB, BIT3, OUTPUT); //useless
	//gpioPinWrite(GPIOB, BIT3,BIT3);
/*
	g8_SwICU_value=TCNT0;
	volatile static uint8_t counter=0;
	g8_gloabal_int0_flag=1;
	if(counter==0)
	{
		gpioPinWrite(GPIOB, BIT3,BIT3);
		US_start();
		counter++;
	}
	else if(counter==1)
	{
		gpioPinWrite(GPIOB, BIT3,LOW);
		US_stop();
	    g8_global_distance= (uint8_t)(g8_SwICU_value*8/60);
	    TCNT1=g8_global_distance;
	    TCNT0=0;
	    counter=0;
	}
*/
	/*
	volatile static uint8_t counter=0;
	uint8_t x;
	uint8_t distance;
	g8_gloabal_int0_flag=1;
	gpioPinDirection(GPIOB, BIT3, OUTPUT); //useless
	//gpioPinToggle(GPIOB,BIT3);
	if(0==counter)
	{
		timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,0,T0_INTERRUPT_NORMAL);
		counter++;
	}
	else if(counter==1)
	{
		gpioPinToggle(GPIOB,BIT3);
		x=TCNT0;
		US_stop();
	    distance= (uint8_t)(x/15);
	    gpioPortDirection(2,OUTPUT);
	    gpioPortWrite(2,10);
	    TCNT0=0;
	    counter=0;
	}
	*/

	/*
	g8_gloabal_int0_flag=1;
	uint8_t x;
	x=TCNT0;
	TCNT0=0;
	TCNT1=x;
	//x/=2;
	gpioPinDirection(GPIOB, BIT3, OUTPUT); //useless
	gpioPinToggle(GPIOB,BIT3);
	uint16_t time=((x*4)/2);
	//uint8_t distance=(uint8_t)((time*340*100)/1000000);
	uint8_t distance= (uint8_t)(x*2/60);
	//uint8_t distance= (uint8_t)(x*8/60);
	//uint8_t distance=d;
	TCNT2=distance;
	gpioPortDirection(GPIOB,OUTPUT);
	gpioPortWrite(GPIOB,distance);
*/
//}

/*****************************************************************************/

/*******************************these ISRs for UART****************************************/
/*
ISR(USART_RXC_vect)
{
	if(g_UART_sender_CallBackPtr != NULL_PTR)
	{
		// Call the Call Back function in the application after the edge is detected
		(*g_UART_sender_CallBackPtr)(); // another method to call the function using pointer to function g_callBackPtr();
	}
}

ISR(USART_TXC_vect)
{
	if(g_UART_receiver_CallBackPtr != NULL_PTR)
	{
		//Call the Call Back function in the application after the edge is detected
		(*g_UART_receiver_CallBackPtr)(); // another method to call the function using pointer to function g_callBackPtr();
	}
}
*/


/**************************these ISRs for UART & SPI Challenge****************************/


ISR(TIMER0_COMP_vect)
{
	timer0_compare_match_tickes++;
	TCNT0=0;
}


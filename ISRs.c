/*
 ============================================================================
 Name        : ISRs.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */
#include "ISRs.h"

volatile uint8_t g8_gloabal_int0_flag=0;

/****************this ISRs for testing*****************/
/*
ISR(INT0_vect)
{
	//gpioPinDirection(GPIOB, BIT1, OUTPUT);
	//gpioPinToggle(GPIOB,BIT1);
	g8_gloabal_int0_flag=1;
}
*/
/****************this ISRs for state machine using interrupt*****************/
/*
ISR(TIMER0_COMP_vect)
{
	static uint16_t u16_timer_tick=0;
	if(u16_timer_tick==1000)
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
}

ISR(INT0_vect)
{
	g8_gloabal_int0_flag=1;
}
*/
/*****************************************************************************/


/****************************these ISRs for SWPWM****************************/

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

/*****************************************************************************/


/*******************************these ISRs for Ultrasonic sensor*******************************************/
/*
ISR(INT0_vect)
{
	g8_SwICU=TCNT0;
	gpioPinDirection(GPIOB, BIT0, OUTPUT);
	gpioPinWrite(GPIOB, BIT0,BIT0);
}
*/
/*****************************************************************************/


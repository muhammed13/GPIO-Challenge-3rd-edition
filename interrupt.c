/*
 ============================================================================
 Name        : interrupt.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */
#include "interrupt.h"
#include "led.h"
uint8_t g8_state;
uint8_t g8_interrupt_zero_flag=0;

/***********************TIMER0*********************************/
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
*/

/*this is for implementing an inverted wave form*/
/*
ISR(TIMER0_OVF_vect)
{
	volatile static uint16_t u16_motor_tick=0;
	volatile uint16_t duty=(250*g8_gloabal_car_duty)/100;
	if(u16_motor_tick==duty)
	{
		gpioPinWrite(GPIOD, BIT4,BIT4);
		gpioPinWrite(GPIOD, BIT5,BIT5);
	}
	if(u16_motor_tick<duty)
	{
		gpioPinWrite(GPIOD, BIT4,LOW);
		gpioPinWrite(GPIOD, BIT5,LOW);
	}
	if(u16_motor_tick==250)
	{
		u16_motor_tick=0;
	}
	TCNT0=6;
	u16_motor_tick++;
}
*/
/*this ISR for wave form generation on pin 7 portB*/
/*
ISR(TIMER0_COMP_vect)
{
	static uint16_t u16_timer_tick=0;
	gpioPinToggle(GPIOB, BIT7);
	u16_timer_tick=0;
	u16_timer_tick++;
}
*/


/*these ISRs for test the soft PWM*/
/*
ISR(TIMER0_COMP_vect)
{
	gpioPinWrite(GPIOB, BIT3,BIT3);
}
ISR(TIMER0_OVF_vect)
{
	gpioPinWrite(GPIOB, BIT3,LOW);
	TCNT0=6;
}
*/

ISR(TIMER0_COMP_vect)
{
	Led_On(LED_0);
	gpioPinWrite(GPIOD, BIT4,BIT4);
	gpioPinWrite(GPIOD, BIT5,BIT5);
}
ISR(TIMER0_OVF_vect)
{
	Led_Off(LED_0);
	gpioPinWrite(GPIOD, BIT4,LOW);
	gpioPinWrite(GPIOD, BIT5,LOW);
	TCNT0=100;
}

/************************INT0*****************************************/
void INT0_Init(void)
{
	cli();                              /*Disable interrupts by clearing I-bit*/
	GICR  |= (1<<INT0);                 /* Enable external interrupt pin INT0*/
	MCUCR |= (1<<ISC00) | (1<<ISC01);   /* Trigger INT0 with the raising edge*/
	sei();                              /*Enable interrupts by setting I-bit*/
}


ISR(INT0_vect)
{
	g8_interrupt_zero_flag=1;
}

/***********************************************************************/

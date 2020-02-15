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

/************************INT0*****************************************/
void INT0_Init(EN_Edge_t en_edge_selection)
{
	cli();                              /*Disable interrupts by clearing I-bit*/
	GICR  |= (1<<INT0);                 /* Enable external interrupt pin INT0*/
	gpioPinDirection(GPIOD,BIT2,INPUT);  /*set INT0 pin as input */
	switch(en_edge_selection)
	{
	case LOW_LEVEL:
								/* Trigger INT0 with the low level*/
		break;

	case ANY_CHANGE:
		MCUCR |= (1<<ISC10);   /* Trigger INT0 with the any change*/
		break;

	case FALLING_EDGE:
		MCUCR |= (1<<ISC00);   /* Trigger INT0 with the falling edge*/
		break;

	case RISIGING_EDGE:
		MCUCR |= (1<<ISC00) | (1<<ISC01);   /* Trigger INT0 with the raising edge*/
		break;
	}
	sei();                              /*Enable interrupts by setting I-bit*/
}


void INT0_DeInit(void)
{
	cli();                              /*Disable interrupts by clearing I-bit*/
	GICR  &= ~(1<<INT0);                 /* Disable external interrupt pin INT0*/
	MCUCR &= ~(1<<ISC00) & ~(1<<ISC01);
}

/****************************INT1*******************************************/
void INT1_Init(EN_Edge_t en_edge_selection)
{
	cli();                              /*Disable interrupts by clearing I-bit*/
	GICR  |= (1<<INT1);                 /* Enable external interrupt pin INT1*/
	gpioPinDirection(GPIOD,BIT3,INPUT); /*set INT1 pin as input*/
	switch(en_edge_selection)
	{
	case LOW_LEVEL:
								/* Trigger INT0 with the low level*/
		break;

	case ANY_CHANGE:
		MCUCR |= (1<<ISC10);   /* Trigger INT0 with the any change*/
		break;

	case FALLING_EDGE:
		MCUCR |= (1<<ISC00);   /* Trigger INT0 with the falling edge*/
		break;

	case RISIGING_EDGE:
		MCUCR |= (1<<ISC00) | (1<<ISC01);   /* Trigger INT0 with the raising edge*/
		break;
	}
	sei();                              /*Enable interrupts by setting I-bit*/
}

void INT1_DeInit(void)
{
	cli();                              /*Disable interrupts by clearing I-bit*/
	GICR  &= ~(1<<INT1);                 /* Disable external interrupt pin INT0*/
	MCUCR &= ~(1<<ISC00) & ~(1<<ISC01);
	sei();                              /*Enable interrupts by setting I-bit*/
}

/****************************INT2*******************************************/
void INT2_Init(EN_Edge_t en_edge_selection)
{
	cli();                              /*Disable interrupts by clearing I-bit*/
	GICR  |= (1<<INT2);                 /* Enable external interrupt pin INT1*/
	gpioPinDirection(GPIOB,BIT2,INPUT); /*set INT2 pin as input*/
	switch(en_edge_selection)
	{
	case LOW_LEVEL:
								/* Trigger INT0 with the low level*/
		break;

	case ANY_CHANGE:
		MCUCR |= (1<<ISC10);   /* Trigger INT0 with the any change*/
		break;

	case FALLING_EDGE:
		MCUCR |= (1<<ISC00);   /* Trigger INT0 with the falling edge*/
		break;

	case RISIGING_EDGE:
		MCUCR |= (1<<ISC00) | (1<<ISC01);   /* Trigger INT0 with the raising edge*/
		break;
	}
	sei();                              /*Enable interrupts by setting I-bit*/
}

void INT2_DeInit(void)
{
	cli();                              /*Disable interrupts by clearing I-bit*/
	GICR  &= ~(1<<INT2);                 /* Disable external interrupt pin INT0*/
	MCUCR &= ~(1<<ISC00) & ~(1<<ISC01);
	sei();                              /*Enable interrupts by setting I-bit*/
}
/***************************************************************************/

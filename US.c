/*
 ============================================================================
 Name        : US.C
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

/******************************includes************************************/
#include "US.h"
/**************************************************************************/

/******************************define************************************/
#define DOWN 0
/**************************************************************************/

/*****************************global variables****************************/


/************************************************************************/

/********************************functions********************************/
void US_init(void)
{
	gpioPinDirection(GPIOA, BIT0,OUTPUT);
	SwICU_Init(SwICU_EdgeRisiging);
}

void US_triger(void)
{
	gpioPinWrite(US_TRIGGER_GPIO,US_TRIGGER_BIT,US_TRIGGER_BIT);
	softwareDelayMs(10);
	gpioPinWrite(US_TRIGGER_GPIO,US_TRIGGER_BIT,LOW);
}

void US_start(void)
{
	SwICU_Start();
}

void US_stop(void)
{
	SwICU_Disable();
}

uint8_t US_get_reading(void)
{
	/*1 cm = 29.41 us    with 64 pre 7.3 ticks
	 * 15 cm= 441.17 us  with 64 pre 110 ticks
	 * 1 m = 2941.1 us   with 1024 pre 45.9 ticks
	 * 4 m = 11764.7 us  with 1024 pre 183.8 ticks
	 * 15 m =44117.6 us */

	volatile uint8_t u8_timer_ticks;
	uint8_t u8_distance;
	while(g8_gloabal_int0_flag==DOWN);
	g8_gloabal_int0_flag=DOWN;
	SwICU_Read(&u8_timer_ticks);
	u8_distance=u8_timer_ticks/7;
	return u8_distance;
}

void US_deinit(void)
{

}
/**************************************************************************/

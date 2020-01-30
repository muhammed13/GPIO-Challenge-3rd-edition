/*
 ============================================================================
 Name        : SwICU.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#include "SwICU.h"
volatile uint8_t g8_SwICU;

void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge)
{
	INT0_Init(a_en_inputCaptureEdge);
	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_1024,0,0,T0_INTERRUPT_NORMAL);
}


void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge)
{

}


void SwICU_Read(volatile uint8_t * a_pu8_capt)
{
	*a_pu8_capt=g8_SwICU;
}

void SwICU_Start(void)
{
	/* one timer tick = 4 (us) for 64 prescaller
	 * one timer tick = 16 (us) for 256 prescaller
	 * one timer tick = 64 (us) for 1024 prescaller
	 * */
	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,0,T0_INTERRUPT_NORMAL);
}

void SwICU_Stop(void)
{
	timer0Stop();
}

void SwICU_Enable(void)
{

}

void SwICU_Disable(void)
{
	timer0Stop();
	INT0_DeInit();
}


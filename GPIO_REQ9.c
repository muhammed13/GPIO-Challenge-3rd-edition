#include "GPIO_REQ9.h"
void trafficlight(void)
{
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	en_STATE state=GO_;
	while(TRUE)
	{
		switch(state)
		{
			case GO_:
				Led_On(LED_1);
				softwareDelayMs(ONE_SEC_);
				Led_Off(LED_1);
				state=STOP_;
				break;
			case READY_:
				Led_On(LED_2);
				softwareDelayMs(ONE_SEC_);
				Led_Off(LED_2);
				state=GO_;
				break;
			case STOP_:
				Led_On(LED_3);
				softwareDelayMs(ONE_SEC_);
				Led_Off(LED_3);
				state=READY_;
				break;
		}

	}
}

void trafficlight_using_timer0(void)
{
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	en_STATE state=GO_;
	while(TRUE)
	{
		switch(state)
		{
			case GO_:
				Led_On(LED_1);
				timer0DelayMs(ONE_SEC_);
				Led_Off(LED_1);
				state=STOP_;
				break;
			case READY_:
				Led_On(LED_2);
				timer0DelayMs(ONE_SEC_);
				Led_Off(LED_2);
				state=GO_;
				break;
			case STOP_:
				Led_On(LED_3);
				timer0DelayMs(ONE_SEC_);
				Led_Off(LED_3);
				state=READY_;
				break;
		}

	}
}


void trafficlight_using_timer1(void)
{
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	en_STATE state=GO_;
	while(TRUE)
	{
		switch(state)
		{
			case GO_:
				Led_On(LED_1);
				timer1DelayMs(ONE_SEC_);
				Led_Off(LED_1);
				state=STOP_;
				break;
			case READY_:
				Led_On(LED_2);
				timer1DelayMs(ONE_SEC_);
				Led_Off(LED_2);
				state=GO_;
				break;
			case STOP_:
				Led_On(LED_3);
				timer1DelayMs(ONE_SEC_);
				Led_Off(LED_3);
				state=READY_;
				break;
		}

	}
}


void trafficlight_using_timer0_using_interrupts(void)
{
	sei();
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
    g8_state=GO_;
	timer0Init(T0_COMP_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,MS_OCR_value,T0_INTERRUPT_CMP);
	while(TRUE)
	{

	}
}


void trafficlight_using_timer0_using_interrupts_button(void)
{
	INT2_Init(RISIGING_EDGE);
	g8_gloabal_int0_flag=0;
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	while(TRUE)
	{
		if(g8_gloabal_int0_flag==1)
		{
		    g8_state=STOP_;
			timer0Init(T0_COMP_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,MS_OCR_value,T0_INTERRUPT_CMP);
			g8_gloabal_int0_flag=0;
		}
	}
}

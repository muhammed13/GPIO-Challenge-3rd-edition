/*
 ============================================================================
 Name        : AGILE_REQ2.h
 Author      : Muhammed Gamal
 Description :this file contains the timer driver
 ============================================================================
 */


/*********************************includes**********************************/
#include "timers.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define TIMER_ICR1_TOP_VALUE 2499
/***************************************************************************/


/******************************global variables*****************************/
uint8_t g8_TCNT0_value_Swpwm_ISR;

/***************************************************************************/


/******************************static functions*****************************/

/***************************************************************************/


/*==============================Timer0===============================*/
/*************************************************************************
* Function Name: timer0Init
* Sync/Async: Asynchronous
* Reentrancy: None_reentrant
* Parameters (in): en_mode - ENUM that defines the timer mode
*                  en_OC0 - ENUM that defines the mode of OC0 PIN
*                  en_prescal - ENUM that defines the clock prescaller
*                  u8_initialValue -uint8_t that defines the initial value of TCNT
*                  u8_outputCompare -uint8_t that defines the output compare value
*                  en_interruptMask -ENUM that defines interrupt mode
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:this function initialize timer0 by defining the values of
* TCNT0,TIMSK,OCR0 and TCCR0
* ***********************************************************************/
void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,
		En_timer0perscaler_t en_prescal, uint8_t u8_initialValue,
		uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask)
{

	switch (en_mode)
	{
	case T0_NORMAL_MODE:
		TCNT0 = u8_initialValue; /*timer initial value*/
		TIMSK = en_interruptMask; /*disable or choose the interrupt*/
		OCR0 = u8_outputCompare;
		/* Configure the timer control register
		 * 1. Non PWM mode FOC0=1
		 * 2. Normal Mode WGM01=0 & WGM00=0
		 * 3. Normal Mode COM00=0 & COM01=0
		 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
		 */
		TCCR0 = en_prescal | en_OC0 | (1<<FOC0);   /*I made switch case because of FOC0 will be disabled to zero in the PWM mode*/
		break;

	case T0_COMP_MODE:
		TCNT0 = u8_initialValue; /*timer initial value*/
		OCR0 = u8_outputCompare; /*set the compare value*/
		TIMSK = en_interruptMask; /*disable or choose the interrupt*/

		/* Configure the timer control register
		 * 1. Non PWM mode FOC0=1
		 * 2. Normal Mode WGM01=0 & WGM00=0
		 * 3. Normal Mode COM00=0 & COM01=0
		 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
		 */
		TCCR0= en_prescal | en_OC0 | (1<<FOC0);
		break;
	}
}

/*************************************************************************
* Function Name: timer0Set
* Parameters (in): u8_value - uint8_t value that defines the TCNT0 value
* Return value: None
* Description:this function sets a value in TCNT0 register
* ***********************************************************************/
void timer0Set(uint8_t u8_value)
{
	TCNT0 = u8_value;
}

/*************************************************************************
* Function Name: timer0Read
* Parameters (in): None
* Return value: TCNT0_value - uint8_t variable that holds the value  of TCNT0
* Description:this function reads the value of TCNT0 register
* ***********************************************************************/
uint8_t timer0Read(void)
{
	uint8_t TCNT0_value=TCNT0;
	return TCNT0_value;
}

/*************************************************************************
* Function Name: timer0Start
* Parameters (in): None
* Return value: None
* Description:this function sets the timer clock without prescaller
* ***********************************************************************/
void timer0Start(void)
{
	TCCR0 = T0_PRESCALER_NO;
}

/*************************************************************************
* Function Name: timer0Stop
* Parameters (in): None
* Return value: None
* Description:this function stops timer0 by stopping the timer clock
* ***********************************************************************/
void timer0Stop(void)
{
	TCCR0 = T0_NO_CLOCK;
}

/*************************************************************************
* Function Name: timer0DelayMs
* Parameters (in): u16_delay_in_ms - uint8_t defines the number of MS
* Return value: None
* Description:this function makes a delay in MS using timer0 with pooling
* ***********************************************************************/
void timer0DelayMs(uint16_t u16_delay_in_ms)
{
	/*CTC WITH POOLING*/
	/*this is the equation of ms_OCR_value
	((SEC/(1/(cpu_frq/T0_PRESCALER_64)))/TIMER0_OVER_FLOW_VALUE);
	*/
	timer0Init(T0_COMP_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,MS_OCR_value,T0_POLLING);
	while(u16_delay_in_ms)
	{
		while(BIT_IS_CLEAR(TIFR,OCF0));   /*while(TCNT<OCR0) this condition will handle 1.01s */
		SET_BIT(TIFR,OCF0);
		TCNT0=0;
		u16_delay_in_ms--;
	}
	timer0Stop();
}

/*************************************************************************
* Function Name: timer0DelayMs_with_interrupt
* Parameters (in): u16_delay_in_ms - uint16_t defines the number of MS
* Return value: None
* Description:this function makes a delay in MS using timer0 with interrupt
* ***********************************************************************/
void timer0DelayMs_with_interrupt(uint16_t u16_delay_in_ms)
{
	/*CTC WITH POOLING*/
	/*this is the equation of ms_OCR_value
	((SEC/(1/(cpu_frq/T0_PRESCALER_64)))/TIMER0_OVER_FLOW_VALUE);
	*/
	timer0Init(T0_COMP_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,MS_OCR_value,T0_INTERRUPT_CMP);
}

/*************************************************************************
* Function Name: timer0DelayUs
* Parameters (in): u32_delay_in_us - uint8_t defines the number of US
* Return value: None
* Description:this function makes a delay in US using timer0 with pooling
* ***********************************************************************/
void timer0DelayUs(uint32_t u32_delay_in_us)
{
	/*CTC WITH POOLING*/
	timer0Init(T0_COMP_MODE,T0_OC0_DIS,T0_PRESCALER_NO,0,US_OCR_value,T0_POLLING);
	while(u32_delay_in_us)
	{
		while(TCNT0<OCR0);    /*another way to check*/
		SET_BIT(TIFR,OCF0);
		TCNT0=0;
		u32_delay_in_us--;
	}
	timer0Stop();
}

/*************************************************************************
* Function Name: timer0HwPWM_Fast
* Parameters (in): u8_dutyCycle - uint8_t defines the duty-cycle
*                  u8_frequency - ENUM defines the PWM frequency
* Return value: None
* Description:in this function the PWM generated using the timer0 FAST PWM mode
 * the caller has to choose one of the defined frequencies
* ***********************************************************************/
void timer0HwPWM_Fast(uint8_t u8_dutyCycle,En_timer0Fastfrequency_t u8_frequency)
{
	TCNT0 = 0; /*timer initial value*/
	TIMSK = 0; /*disable interrupts*/
	OCR0 = (u8_dutyCycle*TIMER0_NUMBER_OF_TICKS)/100; /*output compare value*/

	switch(u8_frequency)
	{
	case(T0_FAST_FREQUENCY_62KHZ):
			/* Configure the timer control register
			 * 1. PWM mode FOC0=0
			 * 2. fast PWM mode WGM01=1 & WGM00=1
			 * 3. clear OC0 on compare match COM00=0 & COM01=1
			 * 4. clock = F_CPU CS00=1 CS01=0 CS02=0
			 */
			TCCR0 =T0_PRESCALER_NO | (1<<COM01)| (1<<WGM00) | (1<<WGM01);
			break;

	case(T0_FAST_FREQUENCY_8KHZ):
			/* Configure the timer control register
			 * 1. PWM mode FOC0=0
			 * 2. fast PWM mode WGM01=1 & WGM00=1
			 * 3. clear OC0 on compare match COM00=0 & COM01=1
			 * 4. clock = F_CPU/8 CS00=1 CS01=0 CS02=0
			 */
			TCCR0 =T0_PRESCALER_8 | (1<<COM01)| (1<<WGM00) | (1<<WGM01);
			break;

	case(T0_FAST_FREQUENCY_1KHZ):
			/* Configure the timer control register
			 * 1. PWM mode FOC0=0
			 * 2. fast PWM mode WGM01=1 & WGM00=1
			 * 3. clear OC0 on compare match COM00=0 & COM01=1
			 * 4. clock = F_CPU/64 CS00=1 CS01=1 CS02=0
			 */
			TCCR0 =T0_PRESCALER_64 | (1<<COM01)| (1<<WGM00) | (1<<WGM01);
			break;

	case(T0_FAST_FREQUENCY_244HZ):
			/* Configure the timer control register
			 * 1. PWM mode FOC0=0
			 * 2. fast PWM mode WGM01=1 & WGM00=1
			 * 3. clear OC0 on compare match COM00=0 & COM01=1
			 * 4. clock = F_CPU/256 CS00=0 CS01=0 CS02=1
			 */
			TCCR0 =T0_PRESCALER_256 | (1<<COM01)| (1<<WGM00) | (1<<WGM01);
			break;

	case(T0_FAST_FREQUENCY_61HZ):
			/* Configure the timer control register
			 * 1. PWM mode FOC0=0
			 * 2. fast PWM mode WGM01=1 & WGM00=1
			 * 3. clear OC0 on compare match COM00=0 & COM01=1
			 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
			 */
			TCCR0 =T0_PRESCALER_1024 | (1<<COM01)| (1<<WGM00) | (1<<WGM01);
			break;
	}
}

/*************************************************************************
* Function Name: timer0HwPWM_PhaseCorrect
* Parameters (in): u8_dutyCycle - uint8_t defines the duty-cycle
*                  u8_frequency - ENUM defines the PWM frequency
* Return value: None
* Description:in this function the PWM generated using the timer0 PHASE-CORRECT PWM mode
 * the caller has to choose one of the defined frequencies
* ***********************************************************************/
void timer0HwPWM_PhaseCorrect(uint8_t u8_dutyCycle,En_timer0PhaseCorrectfrequency_t u8_frequency)
{
	TCNT0 = 0; /*timer initial value*/
	TIMSK = 0; /*disable interrupts*/
	OCR0 = (u8_dutyCycle*TIMER0_NUMBER_OF_TICKS)/100; /*output compare value*/

	switch(u8_frequency)
	{
	case(T0_PHASE_CORRECT_FREQUENCY_31KHZ):
			/* Configure the timer control register
			 * 1. PWM mode FOC0=0
			 * 2. phase correct PWM mode WGM01=0 & WGM00=1
			 * 3. clear OC0 on compare match COM00=0 & COM01=1
			 * 4. clock = F_CPU CS00=1 CS01=0 CS02=0
			 */
			TCCR0 =T0_PRESCALER_NO | (1<<COM01)| (1<<WGM00);
			break;

	case(T0_PHASE_CORRECT_FREQUENCY_4KHZ):
			/* Configure the timer control register
			 * 1. PWM mode FOC0=0
			 * 2. phase correct PWM mode WGM01=0 & WGM00=1
			 * 3. clear OC0 on compare match COM00=0 & COM01=1
			 * 4. clock = F_CPU/8 CS00=1 CS01=0 CS02=0
			 */
			TCCR0 =T0_PRESCALER_8 | (1<<COM01)| (1<<WGM00);
			break;

	case(T0_PHASE_CORRECT_FREQUENCY_500HZ):
			/* Configure the timer control register
			 * 1. PWM mode FOC0=0
			 * 2. phase correct PWM mode WGM01=0 & WGM00=1
			 * 3. clear OC0 on compare match COM00=0 & COM01=1
			 * 4. clock = F_CPU/64 CS00=1 CS01=1 CS02=0
			 */
			TCCR0 =T0_PRESCALER_64 | (1<<COM01)| (1<<WGM00);
			break;

	case(T0_PHASE_CORRECT_FREQUENCY_122HZ):
			/* Configure the timer control register
			 * 1. PWM mode FOC0=0
			 * 2. phase correct PWM mode WGM01=0 & WGM00=1
			 * 3. clear OC0 on compare match COM00=0 & COM01=1
			 * 4. clock = F_CPU/256 CS00=0 CS01=0 CS02=1
			 */
			TCCR0 =T0_PRESCALER_256 | (1<<COM01)| (1<<WGM00);
			break;

	case(T0_PHASE_CORRECT_FREQUENCY_31HZ):
			/* Configure the timer control register
			 * 1. PWM mode FOC0=0
			 * 2. phase correct PWM mode WGM01=0 & WGM00=1
			 * 3. clear OC0 on compare match COM00=0 & COM01=1
			 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
			 */
			TCCR0 =T0_PRESCALER_1024 | (1<<COM01)| (1<<WGM00);
			break;
	}
}

/*************************************************************************
* Function Name: timer0SwPWM
* Parameters (in): u8_dutyCycle - uint8_t defines the duty-cycle
*                  u8_frequency - ENUM defines the PWM frequency
* Return value: None
* Description:in this function the PWM generated using the timer0 OUTPUT-COMPARE mode
 * the caller has to choose one of the defined frequencies
* ***********************************************************************/
void timer0SwPWM(uint8_t u8_dutyCycle,En_timer0Swfrequency_t u8_frequency)
{
	uint8_t TCNT0_TEMP;
	uint8_t OCR0_TEMP;
	if(u8_dutyCycle==100)  /*this if statement because at 100% duty cycle the */
	{                      /*TCNT0 will equal OCR0 and the OVF interrupt will be*/
		u8_dutyCycle=99;   /*executed first then the COMP ISR, so this will generate*/
	}                      /*a 0% duty cycle instead of 100%*/
	switch(u8_frequency)
	{
	case T0_SW_FREQUENCY_1KHZ:
			TCNT0_TEMP=6;
			OCR0_TEMP=(u8_dutyCycle)*(250/100.0)+6;
			timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,TCNT0_TEMP,OCR0_TEMP,T0_INTERRUPT_NORMAL|T0_INTERRUPT_CMP);
			break;

	case T0_SW_FREQUENCY_61HZ:
			TCNT0_TEMP=0;
			OCR0_TEMP=(u8_dutyCycle)*(256/100.0);
			timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_1024,TCNT0_TEMP,OCR0_TEMP,T0_INTERRUPT_NORMAL|T0_INTERRUPT_CMP);
			break;
	}
	g8_TCNT0_value_Swpwm_ISR=TCNT0_TEMP;
}

/*==============================Timer1===============================*/

/*************************************************************************
* Function Name: Dio_Init
* Sync/Async: Asynchronous
* Reentrancy: None_reentrant
* Parameters (in): en_mode - ENUM that defines the timer mode
*                  en_OC - ENUM that defines the mode of OC1A/B PIN
*                  en_prescal - ENUM that defines the clock prescaller
*                  u16_initialValue -uint16_t that defines the initial value of TCNT1
*                  u16_outputCompareA -uint16_t that defines the value of OCR1A
*                  u16_outputCompareB -uint16_t that defines the value of OCR1A
*                  u16_inputCapture -uint16_t that defines the value of ICR1
*                  en_interruptMask -ENUM that defines interrupt mode
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:this function initialize timer1 by defining the values of
* TCNT0,TIMSK,OCR1A, OCR1B, ICR1 and TCCR1
* ***********************************************************************/
void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC,
		En_timer1perscaler_t en_prescal, uint16_t u16_initialValue,
		uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,
		uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask)
{

	switch (en_mode)
	{
	case T1_NORMAL_MODE:
		TCNT1H = ((u16_initialValue & 0xFF00)>>8); /*timer initial value*/
		TCNT1L = (u16_initialValue & 0x00FF);
		TIMSK = en_interruptMask; /*disable or choose the interrupt*/

		/* Configure timer control register TCCR1A
	     * 1. mode number 0 (normal mode) WGM11=0 WGM10=0
	     * 2. COM1A1 COM1A0 COM1B1 COM1B0 describe OC1A & OC1B operations according to en_OC
	     * 3. FOC1A=1 FOC1B=1 because these bits are only active in case non-pwm mode)
		 */
		TCCR1A = FOC1A | FOC1B | en_OC;

		/* Configure timer control register TCCR1B
		 * 1. choose the Prescaler using (CS12 CS11 CS10)
		 * 2. mode number 0 (normal mode)   WGM13=0  WGM12=0
	     */
		TCCR1B = en_prescal;
		break;

	case T1_COMP_MODE_OCR1A_TOP:
		TCNT1H = ((u16_initialValue & 0xFF00)>>8); /*timer initial value*/
		TCNT1L = (u16_initialValue & 0x00FF);
		TIMSK = en_interruptMask; /*disable or choose the interrupt*/
		OCR1AH = ((u16_outputCompareA & 0xFF00)>>8); /*set the compare value*/
		OCR1AL = (u16_outputCompareA & 0x00FF);

		/* Configure timer control register TCCR1A
	     * 1. mode number 4 (CTC mode) WGM11=0 WGM10=0
	     * 2. COM1A1 COM1A0 COM1B1 COM1B0 describe OC1A & OC1B operations according to en_OC
	     * 3. FOC1A=1 FOC1B=1 because these bits are only active in case non-pwm mode)
		 */
		TCCR1A = FOC1A | FOC1B | en_OC;

		/* Configure timer control register TCCR1B
		 * 1. mode number 4 (CTC mode_OCR1A)   WGM13=0  WGM12=1
		 * 2. choose the prescaler using (CS12 CS11 CS10)
	     */
		TCCR1B = en_prescal | (1<<WGM12);
		break;

	case T1_COMP_MODE_ICR1_TOP:
		TCNT1H = ((u16_initialValue & 0xFF00)>>8); /*timer initial value*/
		TCNT1L = (u16_initialValue & 0x00FF);
		TIMSK = en_interruptMask; /*disable or choose the interrupt*/
		ICR1H = ((u16_inputCapture & 0xFF00)>>8); /*set the input capture value*/
		ICR1L = (u16_inputCapture & 0x00FF);

		/* Configure timer control register TCCR1A
	     * 1. mode number 4 (CTC mode) WGM11=0 WGM10=0
	     * 2. COM1A1 COM1A0 COM1B1 COM1B0 describe OC1A & OC1B operations according to en_OC
	     * 3. FOC1A=1 FOC1B=1 because these bits are only active in case non-pwm mode)
		 */
		TCCR1A = FOC1A | FOC1B | en_OC;

		/* Configure timer control register TCCR1B
		 * 1. mode number 12 (CTC mode _ICR1)   WGM13=1  WGM12=1
		 * 2. choose the prescaler using (CS12 CS11 CS10)
	     */
		TCCR1B = en_prescal | (1<<WGM12) | (1<<WGM13);
		break;
	}
}

/*************************************************************************
* Function Name: timer1Set
* Parameters (in): u16_value - uint16_t value that defines the TCNT1 value
* Return value: None
* Description:this function sets a value in TCNT1 register
* ***********************************************************************/
void timer1Set(uint16_t u16_value)
{
	TCNT1H = ((u16_value & 0xFF00)>>8); /*timer initial value*/
	TCNT1L = (u16_value & 0x00FF);
}

/*************************************************************************
* Function Name: timer1Read
* Parameters (in): None
* Return value: TCNT16_value - uint16_t variable that holds the value  of TCNT1
* Description:this function reads the value of TCNT1 register
* ***********************************************************************/
uint16_t timer1Read(void)
{
	uint16_t TCNT1_value=TCNT1;
	return TCNT1_value;
}

/*************************************************************************
* Function Name: timer1Start
* Parameters (in): None
* Return value: None
* Description:this function sets the timer clock without prescaller
* ***********************************************************************/
void timer1Start(void)
{
	TCCR1B = T0_PRESCALER_NO;
}

/*************************************************************************
* Function Name: timer1Stop
* Parameters (in): None
* Return value: None
* Description:this function stops timer1 by stopping the timer clock
* ***********************************************************************/
void timer1Stop(void)
{
	TCCR1B = T0_NO_CLOCK;
}

/*************************************************************************
* Function Name: timer1DelayMs
* Parameters (in): u16_delay_in_ms - uint16_t defines the number of MS
* Return value: None
* Description:this function makes a delay in MS using timer1 with pooling
* ***********************************************************************/
void timer1DelayMs(uint16_t u16_delay_in_ms)
{
	/*CTC WITH POOLING*/
	/*this is the equation of ms_OCR_value
	((SEC/(1/(cpu_frq/T0_PRESCALER_64)))/TIMER0_OVER_FLOW_VALUE);
	*/
	timer1Init(T1_COMP_MODE_OCR1A_TOP,T1_OC1_DIS,T1_PRESCALER_64,0,MS_OCR_value,0,0,T0_POLLING);
	while(u16_delay_in_ms)
	{
		while(BIT_IS_CLEAR(TIFR,OCF1A));   /*while(TCNT<OCR1A) this condition will handle 1.01s */
		SET_BIT(TIFR,OCF1A);
		TCNT1=0;
		u16_delay_in_ms--;
	}
	timer1Stop();
}

/*************************************************************************
* Function Name: timer1DelayUs
* Parameters (in): u32_delay_in_us - uint32_t defines the number of US
* Return value: None
* Description:this function makes a delay in US using timer1 with pooling
* ***********************************************************************/
void timer1DelayUs(uint32_t u32_delay_in_us)
{
	/*CTC WITH POOLING*/
	timer1Init(T1_COMP_MODE_OCR1A_TOP,T1_OC1_DIS,T1_PRESCALER_NO,0,US_OCR_value,0,0,T0_POLLING);
	while(u32_delay_in_us)
	{
		while(BIT_IS_CLEAR(TIFR,OCF1A));  /*while(TCNT<OCR1A) this condition will handle 1.01s */
		SET_BIT(TIFR,OCF0);
		TCNT0=0;
		u32_delay_in_us--;
	}
	timer1Stop();
	return;
}

/*************************************************************************
* Function Name: timer1HwPWM_Fast
* Parameters (in): u8_dutyCycle - uint8_t defines the duty-cycle
*                  u8_frequency - ENUM defines the PWM frequency
* Return value: None
* Description:in this function the PWM generated using the timer1 FAST PWM
* mode 14 (fast PWM ICR1 TOP)
* the caller has to choose one of the defined frequencies
* ***********************************************************************/
void timer1HwPWM_Fast(uint8_t u8_dutyCycle,En_timer1Fastfrequency_t u8_frequency)
{
	TCNT1 = 0; /*timer initial value*/
	TIMSK = 0; /*disable interrupts*/
	OCR1A = (u8_dutyCycle)*(TIMER_ICR1_TOP_VALUE/100);   /*output compare value*/
	OCR1B = (u8_dutyCycle)*(TIMER_ICR1_TOP_VALUE/100);   /*output compare value*/

	switch(u8_frequency)
	{

	case(T1_FAST_FREQUENCY_6KHZ):
			ICR1 = TIMER_ICR1_TOP_VALUE;	/* Set TOP count for timer1 in ICR1 register */
			/* Configure timer control register TCCR1A
			 * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
			 * 2. Clear OC1B on compare match (non inverting mode) COM1B1=1 COM1B0=0
			 * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
			 * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
			 */
			TCCR1A = (1<<WGM11) | (1<<COM1A1)  | (1<<COM1B1);

			/* Configure timer control register TCCR1A
			 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
			 * 2. Prescaller = F_CPU
			 */
			TCCR1B = (1<<WGM12) | (1<<WGM13) | T1_PRESCALER_NO;
			break;

	case(T1_FAST_FREQUENCY_800HZ):
			ICR1 = TIMER_ICR1_TOP_VALUE;	/* Set TOP count for timer1 in ICR1 register */
			/* Configure timer control register TCCR1A
			 * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
			 * 2. Clear OC1B on compare match (non inverting mode) COM1B1=1 COM1B0=0
			 * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
			 * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
			 */
			TCCR1A = (1<<WGM11) | (1<<COM1A1)  | (1<<COM1B1);

			/* Configure timer control register TCCR1A
			 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
			 * 2. Prescaller = F_CPU/8
			 */
			TCCR1B = (1<<WGM12) | (1<<WGM13) | T1_PRESCALER_8;
			break;

	case(T1_FAST_FREQUENCY_100HZ):
			ICR1 = TIMER_ICR1_TOP_VALUE;	/* Set TOP count for timer1 in ICR1 register */
			/* Configure timer control register TCCR1A
			 * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
			 * 2. Clear OC1B on compare match (non inverting mode) COM1B1=1 COM1B0=0
			 * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
			 * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
			 */
			TCCR1A = (1<<WGM11) | (1<<COM1A1) | (1<<COM1B1);

			/* Configure timer control register TCCR1A
			 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
			 * 2. Prescaller = F_CPU/64
			 */
			TCCR1B = (1<<WGM12) | (1<<WGM13) | T1_PRESCALER_64;
			break;

	case(T1_FAST_FREQUENCY_25HZ):  //90hz
			ICR1 = TIMER_ICR1_TOP_VALUE;	/* Set TOP count for timer1 in ICR1 register */
			/* Configure timer control register TCCR1A
		     * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
		     * 2. Clear OC1B on compare match (non inverting mode) COM1B1=1 COM1B0=0
		     * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
		     * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
			 */
			TCCR1A = (1<<WGM11) | (1<<COM1A1)  | (1<<COM1B1);

			/* Configure timer control register TCCR1A
			 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
			 * 2. Prescaller = F_CPU/256
		     */
			TCCR1B = (1<<WGM12) | (1<<WGM13) | T1_PRESCALER_256;
			break;

	case(T1_FAST_FREQUENCY_6HZ):
			ICR1 = TIMER_ICR1_TOP_VALUE;	/* Set TOP count for timer1 in ICR1 register */
			/* Configure timer control register TCCR1A
			 * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
			 * 2. Clear OC1B on compare match (non inverting mode) COM1B1=1 COM1B0=0
			 * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
			 * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
			 */
			TCCR1A = (1<<WGM11) | (1<<COM1A1)  | (1<<COM1B1);

			/* Configure timer control register TCCR1A
			 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
			 * 2. Prescaller = F_CPU/1024
			 */
			TCCR1B = (1<<WGM12) | (1<<WGM13) | T1_PRESCALER_1024;
			break;
	}
}

/*************************************************************************
* Function Name: timer1HwPWM_PhaseCorrect
* Parameters (in): u8_dutyCycle - uint8_t defines the duty-cycle
*                  u8_frequency - ENUM defines the PWM frequency
* Return value: None
* Description:in this function the PWM generated using the timer1 PHASE-CORRECT PWM
* mode 10 (phase correct PWM ICR1 TOP)
 * the caller has to choose one of the defined frequencies
* ***********************************************************************/
void timer1HwPWM_PhaseCorrect(uint8_t u8_dutyCycle,En_timer1PhaseCorrectfrequency_t u8_frequency)
{
	TCNT1 = 0; /*timer initial value*/
	TIMSK = 0; /*disable interrupts*/
	OCR1A = (u8_dutyCycle)*(TIMER_ICR1_TOP_VALUE/100);   /*output compare value*/
	OCR1B = (u8_dutyCycle)*(TIMER_ICR1_TOP_VALUE/100);   /*output compare value*/

	switch(u8_frequency)
	{

	case(T1_PHASE_CORRECT_FREQUENCY_3KHZ):
			ICR1 = TIMER_ICR1_TOP_VALUE;	/* Set TOP count for timer1 in ICR1 register */
			/* Configure timer control register TCCR1A
			 * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
			 * 2. Clear OC1B on compare match (non inverting mode) COM1B1=1 COM1B0=0
			 * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
			 * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
			 */
			TCCR1A = (1<<WGM11) | (1<<COM1A1)  | (1<<COM1B1);

			/* Configure timer control register TCCR1A
			 * 1. phase correct Pwm Mode with the TOP in ICR1 WGM12=0 WGM13=1 (Mode Number 10)
			 * 2. Prescaller = F_CPU
			 */
			TCCR1B =(1<<WGM13) | T1_PRESCALER_NO;
			break;

	case(T1_PHASE_CORRECT_FREQUENCY_400HZ):
			ICR1 = TIMER_ICR1_TOP_VALUE;	/* Set TOP count for timer1 in ICR1 register */
			/* Configure timer control register TCCR1A
			 * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
			 * 2. Clear OC1B on compare match (non inverting mode) COM1B1=1 COM1B0=0
			 * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
			 * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
			 */
			TCCR1A = (1<<WGM11) | (1<<COM1A1)  | (1<<COM1B1);

			/* Configure timer control register TCCR1A
			 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
			 * 2. Prescaller = F_CPU/8
			 */
			TCCR1B = (1<<WGM13) | T1_PRESCALER_8;
			break;

	case(T1_PHASE_CORRECT_FREQUENCY_50HZ):
			ICR1 = TIMER_ICR1_TOP_VALUE;	/* Set TOP count for timer1 in ICR1 register */
			/* Configure timer control register TCCR1A
			 * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
			 * 2. Clear OC1B on compare match (non inverting mode) COM1B1=1 COM1B0=0
			 * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
			 * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
			 */
			TCCR1A = (1<<WGM11) | (1<<COM1A1)  | (1<<COM1B1);

			/* Configure timer control register TCCR1A
			 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
			 * 2. Prescaller = F_CPU/64
			 */
			TCCR1B =(1<<WGM13) | T1_PRESCALER_64;
			break;

	case(T1_PHASE_CORRECT_FREQUENCY_13HZ):  //90hz
			ICR1 = TIMER_ICR1_TOP_VALUE;	/* Set TOP count for timer1 in ICR1 register */
			/* Configure timer control register TCCR1A
		     * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
		     * 2. Clear OC1B on compare match (non inverting mode) COM1B1=1 COM1B0=0
		     * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
		     * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
			 */
			TCCR1A = (1<<WGM11) | (1<<COM1A1)  | (1<<COM1B1);

			/* Configure timer control register TCCR1A
			 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
			 * 2. Prescaller = F_CPU/256
		     */
			TCCR1B =(1<<WGM13) | T1_PRESCALER_256;
			break;

	case(T1_PHASE_CORRECT_FREQUENCY_3HZ):
			ICR1 = TIMER_ICR1_TOP_VALUE;	/* Set TOP count for timer1 in ICR1 register */
			/* Configure timer control register TCCR1A
			 * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
			 * 2. Clear OC1B on compare match (non inverting mode) COM1B1=1 COM1B0=0
			 * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
			 * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
			 */
			TCCR1A = (1<<WGM11) | (1<<COM1A1)  | (1<<COM1B1);

			/* Configure timer control register TCCR1A
			 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
			 * 2. Prescaller = F_CPU/1024
			 */
			TCCR1B =(1<<WGM13) | T1_PRESCALER_1024;
			break;
	}
}

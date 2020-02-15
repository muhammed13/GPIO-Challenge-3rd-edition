/*
 ============================================================================
 Name        : UART_SPI_ApplicationMicro2.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


#include "UART_SPI_ApplicationMicro2.h"

void Micro_TwoApplication(void)
{

	sei();
	uint8_t speed=0;
	uint8_t distance=0;
	uint8_t data=0;

	SPI_initSlave();


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


	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);


	gpioPinDirection(GPIOB,BIT3,OUTPUT); //for buzzer
	while(1)
	{

		speed=SPI_recieveByte();

		if(pushButtonGetStatus(BTN_0))
		{
			while(pushButtonGetStatus(BTN_0));
			timer0Init(T0_COMP_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,250,T0_INTERRUPT_CMP);
			distance=0;
		}

		if(pushButtonGetStatus(BTN_1))
		{
			while(pushButtonGetStatus(BTN_1));
			timer0Stop();

			//UART_sendString("the distance is \r");
			UART_sendByte(distance);
		}

		if(timer0_compare_match_tickes>=1000)
		{
			gpioPinToggle(GPIOB,BIT3);
			distance+=(speed-48);
			timer0_compare_match_tickes=0;
		}

	}

}



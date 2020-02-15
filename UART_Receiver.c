/*
 ============================================================================
 Name        : UART_Receiver.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#include "UART_Receiver.h"

void UART_Receiver_func(void)
{
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
}

void UART_Receiver_with_interrupt_func(void)
{
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
}

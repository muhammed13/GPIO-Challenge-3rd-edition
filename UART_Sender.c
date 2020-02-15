/*
 ============================================================================
 Name        : UART_Sender.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


#include "UART_Sender.h"



void UART_Sender_func(void)
{
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
	softwareDelayMs(3000);
	while(1)
	{
		 UART_sendByte(num);
		num++;
		if(num==15)
		{
			num=0;
		}
		softwareDelayMs(500);
	}
}


void UART_Sender_with_interrupt_func(void)
{
	UART_setCallBack(UART_set_UDR);

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

	softwareDelayMs(3000);
	while(1)
	{
		 UART_sendByte(g8_udr_data);
		 g8_udr_data++;
		if(g8_udr_data==15)
		{
			g8_udr_data=0;
		}
		softwareDelayMs(500);
	}
}


void UART_setCallBack(void(*a_ptr)(void))
{
	// Save the address of the Call back function in a global variable
	g_UART_sender_CallBackPtr = a_ptr;
}


/*
 ============================================================================
 Name        : UART_SPI_Application.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


#include "UART_SPI_ApplicationMicro1.h"

volatile uint8_t speed=1;

void Micro_OneApplication(void)
{

	gpioPinDirection(GPIOB,BIT3,OUTPUT); //for buzzer
	gpioPinDirection(GPIOC,BIT3,OUTPUT); //for led


	uint8_t speed=0;


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

	SPI_initMaster();


	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	Led_Init(LED_1);

	softwareDelayMs(500);    /*waiting micro2*/
	UART_sendString("please enter the speed \r");
	speed=UART_recieveByte();
	UART_sendString("the speed is ");
	UART_sendByte(speed);
	while(1)
	{

		if(pushButtonGetStatus(BTN_0))
		{
			while(pushButtonGetStatus(BTN_0));
			speed++;
			gpioPinToggle(GPIOB,BIT3);
		}
		if(pushButtonGetStatus(BTN_1))
		{
			while(pushButtonGetStatus(BTN_1));
			speed--;
			gpioPinToggle(GPIOC,BIT3);
		}
		SPI_sendByte(speed);
		softwareDelayMs(10);
	}
}

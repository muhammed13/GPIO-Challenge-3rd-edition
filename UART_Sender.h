/*
 ============================================================================
 Name        : UART_Sender.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef UART_SENDER_H_
#define UART_SENDER_H_

#include "gpio.h"
#include "UART.h"
#include "softwareDelay.h"

void UART_Sender_func(void);
void UART_Sender_with_interrupt_func(void);
void UART_setCallBack(void(*a_ptr)(void));

#endif /* UART_SENDER_H_ */

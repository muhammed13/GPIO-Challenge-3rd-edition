/*
 ============================================================================
 Name        : UART_Receiver.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef UART_RECEIVER_H_
#define UART_RECEIVER_H_

#include "gpio.h"
#include "UART.h"
#include "softwareDelay.h"

void UART_Receiver_func(void);
void UART_Receiver_with_interrupt_func(void);

#endif /* UART_RECEIVER_H_ */

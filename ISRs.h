/*
 ============================================================================
 Name        : ISRs.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef ISRS_H_
#define ISRS_H_
#include "interrupt.h"
#include "timers.h"
#include "led.h"
#include "US.h"
#include "AGILE_REQ2.h"
#include "UART.h"
/***************************global variables************************/
extern uint8_t g8_state;
extern uint8_t g8_gloabal_car_duty;
extern volatile uint8_t g8_gloabal_int0_flag;
extern volatile uint32_t timer0_compare_match_tickes;
/*******************************************************************/
#endif /* ISRS_H_ */

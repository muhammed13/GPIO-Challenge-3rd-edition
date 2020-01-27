#ifndef GPIO_REQ9_H_
#define GPIO_REQ9_H_


#include "led.h"
#include "softwareDelay.h"
#include "interrupt.h"
#include "pushButton.h"

#ifndef ONE_SEC_
#define ONE_SEC_ 1000
#endif

#ifndef START
#define START 0
#endif

typedef enum STATE
{
	GO_=1,
	READY_=2,
	STOP_=3,
}STATE;

void trafficlight();

void trafficlight_using_timer0();

void trafficlight_using_timer1();

void trafficlight_using_timer0_using_interrupts();

void trafficlight_using_timer0_using_interrupts_button();

/*global variables */

#endif /* GPIO_REQ7_H_ */

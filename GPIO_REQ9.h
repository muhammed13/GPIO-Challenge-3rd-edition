#ifndef GPIO_REQ9_H_
#define GPIO_REQ9_H_


#include "led.h"
#include "softwareDelay.h"
#include "interrupt.h"
#include "ISRs.h"
#include "pushButton.h"

#ifndef ONE_SEC_
#define ONE_SEC_ 1000
#endif

#ifndef START
#define START 0
#endif

typedef enum en_STATE
{
	GO_=1,
	READY_=2,
	STOP_=3,
}en_STATE;

void trafficlight(void);

void trafficlight_using_timer0(void);

void trafficlight_using_timer1(void);

void trafficlight_using_timer0_using_interrupts(void);

void trafficlight_using_timer0_using_interrupts_button(void);

/*global variables */

#endif /* GPIO_REQ7_H_ */

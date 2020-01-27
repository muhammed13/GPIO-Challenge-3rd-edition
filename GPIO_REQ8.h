#ifndef GPIO_REQ8_H_
#define GPIO_REQ8_H_
#include "led.h"
#include "pushButton.h"
#include "softwareDelay.h"

#ifndef ONE_SEC
#define ONE_SEC 1000
#endif

#ifndef START
#define START_ 0
#endif



void button_led(void);
void button_led_using_timer0(void);
#endif /* GPIO_REQ8_H_ */

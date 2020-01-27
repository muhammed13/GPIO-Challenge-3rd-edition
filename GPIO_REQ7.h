#ifndef GPIO_REQ7_H_
#define GPIO_REQ7_H_


#include "led.h"
#include "pushButton.h"
#include "sevenSeg.h"
#include "softwareDelay.h"


#define MAX_NUMBER 9
#define SWITCHING_TIME 5
#define NUMBER_OF_ITERATION_FOR_ONE_SEC 50
#ifndef ONE_SEC
#define ONE_SEC 1000
#endif

#ifndef START
#define START_ 0
#endif

void sevensegments();

#endif /* GPIO_REQ7_H_ */

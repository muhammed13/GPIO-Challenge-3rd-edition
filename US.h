/*
 ============================================================================
 Name        : US_REQ2.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef US_H_
#define US_H_

#include "SwICU.h"
#include "US_Config.h"
#include "ISRs.h"
/************************definitions*******************************/
#define SOUND_SPEED 340
/******************************************************************/


/**************************global variables************************/

/******************************************************************/


/**************************functions************************/
void US_init(void);
void US_triger(void);
void US_start(void);
void US_stop(void);
uint8_t US_get_reading(void);
/******************************************************************/

#endif /* US_H_ */
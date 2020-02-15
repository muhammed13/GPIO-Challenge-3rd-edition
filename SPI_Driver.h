/*
 ============================================================================
 Name        : SPI_Driver.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include "gpio.h"
#include "registers.h"
#include "SPI_DriverConfig.h"
#include "common_macros.h"

/*******************************Registers Bits Definitions*********************************/
/*****************SPCR*************/
#define SPIE 	7
#define SPE 	6
#define DORD 	5
#define MSTR 	4
#define CPOL 	3
#define CPHA 	2
#define SPR1	1
#define SPR0	0
/*****************SPSR*************/
#define SPIF	7
#define WCOL	6
#define SPI2X	0
/*******************************************************************/

/*********************************functions***************************************/
void SPI_initMaster(void);
void SPI_initSlave(void);
void SPI_sendByte(const uint8_t data);
uint8_t SPI_recieveByte(void);
void SPI_SendString(const uint8_t *Str);
void SPI_ReceiveString(char *Str);

#endif /* SPI_DRIVER_H_ */

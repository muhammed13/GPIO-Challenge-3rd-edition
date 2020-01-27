#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "registers.h"
#include "timers.h"

#define INT0_vect			__vector_1
#define INT1_vect			__vector_2
#define INT2_vect			__vector_3
#define TIMER2_COMP_vect	__vector_4
#define TIMER2_OVF_vect		__vector_5
#define TIMER1_CAPT_vect	__vector_6
#define TIMER1_COMPA_vect	__vector_7
#define TIMER1_COMPB_vect	__vector_8
#define TIMER1_OVF_vect		__vector_9
#define TIMER0_COMP_vect	__vector_10
#define TIMER0_OVF_vect		__vector_11
#define SPI_STC_vect		__vector_12
#define USART_RXC_vect		__vector_13
#define USART_UDRE_vect		__vector_14
#define USART_TXC_vect		__vector_15
#define ADC_vect			__vector_16
#define EE_RDY_vect			__vector_17
#define ANA_COMP_vect		__vector_18
#define TWI_vect			__vector_19
#define SPM_RDY_vect		__vector_20

/*
 * external interrupt registers
 *
 */
/*MCUCR register*/

#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
#define SM0 4
#define SM1 5
#define SM2 6
#define SE 7

/*MCUCSR*/
#define PORF 0
#define EXTRF 1
#define BORF 2
#define WDRF 3
#define JTRF 4
/*reserved bit(bit5)*/
#define ISC2 6
#define JTD 7

/*GICR*/
#define IVCE 0
#define IVSEL 1
/*reserved bit(bit2)*/
/*reserved bit(bit3)*/
/*reserved bit(bit4)*/
#define INT2 5
#define INT0 6
#define INT1 7

/*GIFR*/
/*reserved bit(bit0)*/
/*reserved bit(bit1)*/
/*reserved bit(bit2)*/
/*reserved bit(bit3)*/
/*reserved bit(bit4)*/
#define INTF2 5
#define INTF0 6
#define INTF1 7


/*interrupt macros*/

#define ISR(vector, ...)            \
   void vector (void) __attribute__ ((signal, used, externally_visible)) __VA_ARGS__; \
   void vector (void)

#define sei()  __asm__ __volatile__ ("sei" ::)
#define cli()  __asm__ __volatile__ ("cli" ::)


/* global variables*/
extern uint8_t g8_state;
extern uint8_t g8_interrupt_zero_flag;
extern uint8_t g8_gloabal_car_duty;

/*functions*/
void INT0_Init(void);
#endif /* INTERRUPT_H_ */

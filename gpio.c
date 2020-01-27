#include "gpio.h"
void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction)
{
	switch(u8_port)
	{
	case 0:
			PORTA_DIR=u8_direction;
		break;

	case 1:
			PORTB_DIR=u8_direction;
			break;
	case 2:
			PORTC_DIR=u8_direction;
		break;

	case 3:
			PORTD_DIR=u8_direction;
		break;

	}
}


void gpioPortWrite(uint8_t u8_port, uint8_t u8_value)
{
	switch(u8_port)
	{
	case 0:
			PORTA_DATA=u8_value;

		break;

	case 1:
			PORTB_DATA=u8_value;
		break;

	case 2:
			PORTC_DATA=u8_value;
		break;

	case 3:
			PORTD_DATA=u8_value;
		break;

	}
}

void gpioPortToggle(uint8_t u8_port)
{
	switch(u8_port)
	{
	case 0:
		PORTA_DATA ^= HIGH;
		break;

	case 1:
		PORTB_DATA ^= HIGH;
		break;

	case 2:
		PORTC_DATA ^= HIGH;
		break;

	case 3:
		PORTD_DATA ^= HIGH;
		break;

	}
}

uint8_t gpioPortRead(uint8_t u8_port)
{
	uint8_t data;
	switch(u8_port)
	{
	case 0:
		data=PORTA_PIN;
		break;

	case 1:
		data=PORTB_PIN;
		break;

	case 2:
		data=PORTC_PIN;
		break;
	case 3:
		data=PORTD_PIN;
		break;
	}
	return data;
}

void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction)
{
	switch(u8_port)
	{
	case 0:
		if(u8_direction == INPUT)
		{
			PORTA_DIR &= ~(u8_pins);
		}
		else
		{
			PORTA_DIR |= u8_pins;
		}
		break;

	case 1:
		if(u8_direction == INPUT)
		{
			PORTB_DIR &= ~(u8_pins);
		}
		else
		{
			PORTB_DIR |= u8_pins;
		}
		break;
	case 2:
		if(u8_direction == INPUT)
		{
			PORTC_DIR &= ~(u8_pins);
		}
		else
		{
			PORTC_DIR |= u8_pins;
		}
		break;

	case 3:
		if(u8_direction == INPUT)
		{
			PORTD_DIR &= ~(u8_pins);
		}
		else
		{
			PORTD_DIR |= u8_pins;
		}
		break;

	}
}
/*this function set one bit or more by 1 or 0
 * to write 1 send the pins numbers as u8_pins and u8_value
 * example: gpioPinWrite(PORTA_DATA, BIT3,BIT3);
 * to write 0 send LOW as u8_value and pins numbers as u8_pins
 * example: gpioPinWrite(PORTA_DATA, BIT3,LOW);
 */
void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value)
{
	switch(u8_port)
	{
	case 0:
			PORTA_DATA &= ~(u8_pins);
			PORTA_DATA |= u8_value;

		break;

	case 1:
			PORTB_DATA &= ~(u8_pins);
			PORTB_DATA |= u8_value;
		break;

	case 2:
			PORTC_DATA &= ~(u8_pins);
			PORTC_DATA |= u8_value;
		break;

	case 3:
			PORTD_DATA &= ~(u8_pins);
			PORTD_DATA |= u8_value;
		break;

	}
}

void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins)
{
	switch(u8_port)
	{
	case 0:
			PORTA_DATA ^= u8_pins;
		break;

	case 1:
			PORTB_DATA ^= (u8_pins);
		break;
	case 2:
			PORTC_DATA ^= (u8_pins);
		break;

	case 3:
			PORTD_DATA ^= (u8_pins);
		break;

	}
}

uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin)
{
	uint8_t data;
	switch(u8_port)
	{
	case 0:
		data= (PORTA_PIN & u8_pin);
		break;

	case 1:
		data= (PORTB_PIN & u8_pin);
		break;

	case 2:
		data= (PORTC_PIN & u8_pin);
		break;
	case 3:
		data= (PORTD_PIN & u8_pin);
		break;
	}
	if(data!=LOW)
	{
		data=HIGH;
	}
	return data;
}

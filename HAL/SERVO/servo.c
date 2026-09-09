#define F_CPU 1000000UL
#include "SERVO.h"
#include "DIO_int.h"
#include "Timer0.h"
#include "bitmath.h"
#include <util/delay.h>

#define SERVO_PIN      PIN3
#define SERVO_PORT     DPORTB

#define TCCR0_REG      *((volatile u8*)0x53)
#define OCR0_REG       *((volatile u8*)0x5C)

#define WGM00          3
#define WGM01          6
#define COM00          4
#define COM01          5

void SERVO_Init(void)
{
	DIO_voidSetPinDirection(SERVO_PORT, SERVO_PIN, OUTPUT);
	
	TCCR0_REG = 0;
	SET_BIT(TCCR0_REG, WGM00);
	SET_BIT(TCCR0_REG, WGM01);
	CLEAR_BIT(TCCR0_REG, COM00);
	SET_BIT(TCCR0_REG, COM01);
	TCCR0_REG |= (3 << 0);
	
	OCR0_REG = 0;
}

void SERVO_SetAngle(u8 angle)
{
	if (angle > 180) angle = 180;
	
	u16 pulse_width = (u16)((angle * 10UL) + 50);
	
	OCR0_REG = (u8)pulse_width;
}
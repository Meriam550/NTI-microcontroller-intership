/*
 * day5_lab1_transistor.c
 *
 * Created: 9/5/2026 3:44:28 PM
 * Author : Meriam
 */ 

#define F_CPU 1000000
#include "DIO_int.h"
#include "std.h"
#include <util/delay.h>



int main(void)
{
	DIO_voidSetPinDirection(DPORTC, PIN0, OUTPUT);
	 
    /* Replace with your application code */
    while (1) 
    {
		
		DIO_voidSetPinValue(DPORTC, PIN0, HIGH);
		_delay_ms(5000);
		DIO_voidSetPinValue(DPORTC, PIN0, LOW);
		_delay_ms(1000);
    }
}


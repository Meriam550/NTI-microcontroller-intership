/*
 * day5_lab2_Hbridge.c
 *
 * Created: 9/5/2026 4:20:44 PM
 * Author : Meriam
 */ 

#define F_CPU 1000000UL   
#include <util/delay.h>
#include "DIO_int.h"
#include "std.h"

#define Q1  PIN0
#define Q2  PIN1
#define Q3  PIN2
#define Q4  PIN3


int main(void)
{
	 DIO_voidSetPortDirection(DPORTC, 0xFF);
    /* Replace with your application code */
    while (1) 
    {
		DIO_voidSetPinValue(DPORTC, Q1, HIGH);
		DIO_voidSetPinValue(DPORTC, Q4, HIGH);
		DIO_voidSetPinValue(DPORTC, Q2, LOW);
		DIO_voidSetPinValue(DPORTC, Q3, LOW);
		_delay_ms(5000);
		DIO_voidSetPinValue(DPORTC, Q1, LOW);
		DIO_voidSetPinValue(DPORTC, Q4, LOW);
		DIO_voidSetPinValue(DPORTC, Q2, HIGH);
		DIO_voidSetPinValue(DPORTC, Q3, HIGH);
		_delay_ms(5000);		
		
    }
}


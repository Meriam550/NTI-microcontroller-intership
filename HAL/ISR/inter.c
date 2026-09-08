
/*
 * inter.c
 *
 * Created: 9/6/2026 7:09:40 PM
 *  Author: Meriam
 */ 


#include "std.h"
#include "bitmath.h"
#include "DIO_int.h"
#include "inter.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void INT0_voidInit(void)
{
	
	DIO_voidSetPinDirection(DPORTD, PIN2, INPUT);
	DIO_voidSetPinValue(DPORTD, PIN2, HIGH);   

	
	SET_BIT(MCUCR, 1);
	CLEAR_BIT(MCUCR, 0);

	SET_BIT(GICR, 6); 

	sei();              
}

void INT1_voidInit(void)
{
	
	DIO_voidSetPinDirection(DPORTD, PIN3, INPUT);
	DIO_voidSetPinValue(DPORTD, PIN3, HIGH);   


	SET_BIT(MCUCR, 3);
	CLEAR_BIT(MCUCR, 2);

	SET_BIT(GICR, 7);   

	sei();              
}
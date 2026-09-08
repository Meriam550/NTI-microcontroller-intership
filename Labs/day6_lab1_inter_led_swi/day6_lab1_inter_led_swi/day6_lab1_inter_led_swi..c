/*
 * day6_lab1_inter_led_swi.c
 *
 * Created: 9/6/2026 7:07:08 PM
 * Author : Meriam
 */ 

#define F_CPU 1000000UL
#include "std.h"
#include "DIO_int.h"
#include "bitmath.h"
#include "inter.h"
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	//PORTS of leds
	 DIO_voidSetPinDirection(DPORTC, PIN0, OUTPUT);
	 DIO_voidSetPinDirection(DPORTC, PIN1, OUTPUT);
	 //PORTS of switches
	 DIO_voidSetPinDirection(DPORTC, PIN2, INPUT);
	 DIO_voidSetPinDirection(DPORTC, PIN3, INPUT);
	 
	  INT0_voidInit();
	  INT1_voidInit();
    /* Replace with your application code */
    while (1) 
    {
    }
}
ISR(INT0_vect){
	TOGGLE_BIT(PORTC, PIN0);
}
ISR(INT1_vect){
	TOGGLE_BIT(PORTC, PIN1);
}



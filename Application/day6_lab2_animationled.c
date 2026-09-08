/*
 * day6_lab2_animationled.c
 * Created: 9/6/2026 8:30:48 PM
 * Author : Meriam
 */ 

#define F_CPU 1000000UL
#include "std.h"
#include "DIO_int.h"
#include "bitmath.h"
#include "inter.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile u8 direction = 0; 

int main(void)
{
    
    DIO_voidSetPortDirection(DPORTC, 0xFF);
    DIO_voidSetPortValue(DPORTC, 0); 

    
    INT0_voidInit();

    u8 pins[8] = {PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7};

    while (1) 
    {
        if (direction == 0)
        {
            for (s8 i = 0; i < 8; i++)
            {
                DIO_voidSetPinValue(DPORTC, pins[i], HIGH);
                _delay_ms(200);
                DIO_voidSetPinValue(DPORTC, pins[i], LOW);
                
               
                if (direction != 0) break; 
            }
        }
        else
        {
           
            for (s8 i = 7; i >= 0; i--)
            {
                DIO_voidSetPinValue(DPORTC, pins[i], HIGH);
                _delay_ms(200);
                DIO_voidSetPinValue(DPORTC, pins[i], LOW);
                
                
                if (direction != 1) break; 
            }
        }
    }
}

ISR(INT0_vect)
{
    direction ^= 1; 
}
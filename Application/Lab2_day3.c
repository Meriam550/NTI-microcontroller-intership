/*
 * main.c
 *
 * day3_lab2 - Button-controlled LEDs for ATmega32
 */ 

#include "std.h"
#include "bitmath.h"
#include "DIO_int.h"

int main(void)
{
    /* Configure Switch Pins on PORTA as INPUT */
    DIO_voidSetPinDirection(DPORTA, PIN0, INPUT);
    DIO_voidSetPinDirection(DPORTA, PIN1, INPUT);
    DIO_voidSetPinDirection(DPORTA, PIN2, INPUT);
    DIO_voidSetPinDirection(DPORTA, PIN3, INPUT);
    
    /* Enable Internal Pull-Up Resistors for Switches */
    DIO_voidSetPinValue(DPORTA, PIN0, HIGH);
    DIO_voidSetPinValue(DPORTA, PIN1, HIGH);
    DIO_voidSetPinValue(DPORTA, PIN2, HIGH);
    DIO_voidSetPinValue(DPORTA, PIN3, HIGH);
    
    /* Configure LED Pins on PORTC as OUTPUT */
    DIO_voidSetPinDirection(DPORTC, PIN0, OUTPUT);
    DIO_voidSetPinDirection(DPORTC, PIN1, OUTPUT);
    DIO_voidSetPinDirection(DPORTC, PIN2, OUTPUT);
    
    /* Turn OFF all LEDs initially */
    DIO_voidSetPinValue(DPORTC, PIN0, LOW);
    DIO_voidSetPinValue(DPORTC, PIN1, LOW);
    DIO_voidSetPinValue(DPORTC, PIN2, LOW);

    while (1) 
    {
        /* Check Master Switch (PA3 / Pin 37) */
        if (DIO_u8ReadPinValue(DPORTA, PIN3) == LOW)
        {
            /* Master ON: Turn ON all LEDs */
            DIO_voidSetPinValue(DPORTC, PIN0, HIGH);
            DIO_voidSetPinValue(DPORTC, PIN1, HIGH);
            DIO_voidSetPinValue(DPORTC, PIN2, HIGH);
        }
        else
        {
            /* Individual Switch Control */

            /* Switch 1 (PA0) controls LED 1 (PC0) */
            if (DIO_u8ReadPinValue(DPORTA, PIN0) == LOW)
            {
                DIO_voidSetPinValue(DPORTC, PIN0, HIGH);
            }
            else
            {
                DIO_voidSetPinValue(DPORTC, PIN0, LOW);
            }

            /* Switch 2 (PA1) controls LED 2 (PC1) */
            if (DIO_u8ReadPinValue(DPORTA, PIN1) == LOW)
            {
                DIO_voidSetPinValue(DPORTC, PIN1, HIGH);
            }
            else
            {
                DIO_voidSetPinValue(DPORTC, PIN1, LOW);
            }

            /* Switch 3 (PA2) controls LED 3 (PC2) */
            if (DIO_u8ReadPinValue(DPORTA, PIN2) == LOW)
            {
                DIO_voidSetPinValue(DPORTC, PIN2, HIGH);
            }
            else
            {
                DIO_voidSetPinValue(DPORTC, PIN2, LOW);
            }
        }
    }

    return 0;
}

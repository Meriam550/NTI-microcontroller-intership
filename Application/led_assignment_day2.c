/*
 * main.c
 *
 * Bare-metal ATmega32 — blink an LED on PA0 every 1 second
 * using the HAL LED driver (no direct register access here).
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include "../serv/std.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LED/LED_interface.h"

int main(void)
{
    /* Bring all port directions to the state defined in DIO_config.h */
    DIO_voidInitialization();

    /* LED on Port A, Pin 0, wired active-high (anode → PA0, cathode → GND) */
    LED_Type xLed = { DPORTA, PIN0, ACTIVE_HIGH };

    LED_voidInit(&xLed);

    while (1)
    {
        LED_voidToggle(&xLed);
        _delay_ms(1000);
    }

    return 0;
}

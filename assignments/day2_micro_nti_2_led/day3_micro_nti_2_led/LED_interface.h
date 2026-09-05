/*
 * LED_interface.h
 *
 * HAL driver — LED abstraction layer.
 */

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include "std.h"

/* ACTIVE_HIGH: pin HIGH turns the LED on */
/* ACTIVE_LOW : pin LOW  turns the LED on */
#define ACTIVE_HIGH   1
#define ACTIVE_LOW    0

typedef struct
{
    u8 Port;
    u8 Pin;
    u8 ActiveState;
} LED_Type;

/* Configure the pin as output and leave the LED off. */
void LED_voidInit(LED_Type *Copy_pxLed);

/* Drive the LED on, respecting the active-state polarity. */
void LED_voidTurnOn(LED_Type *Copy_pxLed);

/* Drive the LED off, respecting the active-state polarity. */
void LED_voidTurnOff(LED_Type *Copy_pxLed);

/* Flip the LED from its current state to the opposite. */
void LED_voidToggle(LED_Type *Copy_pxLed);

#endif /* LED_INTERFACE_H */

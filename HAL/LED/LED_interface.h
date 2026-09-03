/*
 * LED_interface.h
 *
 * HAL driver — LED abstraction layer.
 * All hardware access goes through the MCAL DIO driver;
 * no raw register writes live here.
 */

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include "../../serv/std.h"

/* ── Active-state options ───────────────────────────────────────────────── */
#define ACTIVE_HIGH   1
#define ACTIVE_LOW    0

typedef struct
{
    u8 Port;
    u8 Pin;
    u8 ActiveState;
} LED_Type;

/* ── Public API ─────────────────────────────────────────────────────────── */

void LED_voidInit(LED_Type *Copy_pxLed);
void LED_voidTurnOn(LED_Type *Copy_pxLed);
void LED_voidTurnOff(LED_Type *Copy_pxLed);
void LED_voidToggle(LED_Type *Copy_pxLed);

#endif /* LED_INTERFACE_H */

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

/* ACTIVE_HIGH: pin HIGH turns the LED on  (anode tied to MCU pin, cathode to GND) */
/* ACTIVE_LOW : pin LOW  turns the LED on  (cathode tied to MCU pin, anode to VCC) */
#define ACTIVE_HIGH   1
#define ACTIVE_LOW    0

/* ── LED configuration struct ───────────────────────────────────────────── */

/*
 * Fill one of these for every LED in your circuit before calling LED_voidInit.
 *
 *   Port        — one of DPORTA / DPORTB / DPORTC / DPORTD  (from DIO_int.h)
 *   Pin         — one of PIN0 … PIN7                         (from DIO_int.h)
 *   ActiveState — ACTIVE_HIGH or ACTIVE_LOW
 */
typedef struct
{
    u8 Port;
    u8 Pin;
    u8 ActiveState;
} LED_Type;

/* ── Public API ─────────────────────────────────────────────────────────── */

/* Configure the pin as output and leave the LED off. */
void LED_voidInit(LED_Type *Copy_pxLed);

/* Drive the LED on, respecting the active-state polarity. */
void LED_voidTurnOn(LED_Type *Copy_pxLed);

/* Drive the LED off, respecting the active-state polarity. */
void LED_voidTurnOff(LED_Type *Copy_pxLed);

/* Flip the LED from its current state to the opposite. */
void LED_voidToggle(LED_Type *Copy_pxLed);

#endif /* LED_INTERFACE_H */

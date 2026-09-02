/*
 * LED_program.c
 *
 * HAL driver — LED implementation.
 * Every hardware operation is delegated to the MCAL DIO layer;
 * this file never touches PORTA, DDRA, or any AVR register directly.
 */

#include "../../serv/std.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "LED_interface.h"

/* ── LED_voidInit ────────────────────────────────────────────────────────
 * Set the LED pin as output and guarantee the LED starts in the OFF state,
 * regardless of which polarity the hardware uses.
 */
void LED_voidInit(LED_Type *Copy_pxLed)
{
    DIO_voidSetPinDirection(Copy_pxLed->Port, Copy_pxLed->Pin, OUTPUT);

    /* Start with the LED off so the initial state is deterministic. */
    LED_voidTurnOff(Copy_pxLed);
}

/* ── LED_voidTurnOn ──────────────────────────────────────────────────────
 * Illuminate the LED.
 * For ACTIVE_HIGH the pin goes HIGH; for ACTIVE_LOW it goes LOW.
 */
void LED_voidTurnOn(LED_Type *Copy_pxLed)
{
    if (Copy_pxLed->ActiveState == ACTIVE_HIGH)
    {
        DIO_voidSetPinValue(Copy_pxLed->Port, Copy_pxLed->Pin, HIGH);
    }
    else
    {
        DIO_voidSetPinValue(Copy_pxLed->Port, Copy_pxLed->Pin, LOW);
    }
}

/* ── LED_voidTurnOff ─────────────────────────────────────────────────────
 * Extinguish the LED.
 * For ACTIVE_HIGH the pin goes LOW; for ACTIVE_LOW it goes HIGH.
 */
void LED_voidTurnOff(LED_Type *Copy_pxLed)
{
    if (Copy_pxLed->ActiveState == ACTIVE_HIGH)
    {
        DIO_voidSetPinValue(Copy_pxLed->Port, Copy_pxLed->Pin, LOW);
    }
    else
    {
        DIO_voidSetPinValue(Copy_pxLed->Port, Copy_pxLed->Pin, HIGH);
    }
}

/* ── LED_voidToggle ──────────────────────────────────────────────────────
 * Flip the LED from its current state to the opposite.
 *
 * The DIO layer doesn't expose a toggle primitive, so we read the current
 * pin value and write the inverse.  The polarity comparison works for both
 * active-high and active-low: if the pin is in the "ON" state (pin level ==
 * active state) we call TurnOff, otherwise TurnOn.
 */
void LED_voidToggle(LED_Type *Copy_pxLed)
{
    u8 CurrentLevel = DIO_u8ReadPinValue(Copy_pxLed->Port, Copy_pxLed->Pin);

    /*
     * For ACTIVE_HIGH: ON  ↔  pin HIGH (1)
     * For ACTIVE_LOW : ON  ↔  pin LOW  (0)
     * In both cases, ON means CurrentLevel == ActiveState.
     */
    if (CurrentLevel == Copy_pxLed->ActiveState)
    {
        LED_voidTurnOff(Copy_pxLed);
    }
    else
    {
        LED_voidTurnOn(Copy_pxLed);
    }
}

/*
 * LED_program.c
 *
 * HAL driver — LED implementation.
 */

#include "../../serv/std.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "LED_interface.h"

void LED_voidInit(LED_Type *Copy_pxLed)
{
    DIO_voidSetPinDirection(Copy_pxLed->Port, Copy_pxLed->Pin, OUTPUT);
    LED_voidTurnOff(Copy_pxLed);
}

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

void LED_voidToggle(LED_Type *Copy_pxLed)
{
    u8 CurrentLevel = DIO_u8ReadPinValue(Copy_pxLed->Port, Copy_pxLed->Pin);

    if (CurrentLevel == Copy_pxLed->ActiveState)
    {
        LED_voidTurnOff(Copy_pxLed);
    }
    else
    {
        LED_voidTurnOn(Copy_pxLed);
    }
}

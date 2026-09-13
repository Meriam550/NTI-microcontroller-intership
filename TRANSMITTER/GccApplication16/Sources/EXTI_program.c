#include <avr/interrupt.h>
#include "../Headers/Std_types.h"
#include "../Headers/Bit_Math.h"
#include "../Headers/EXTI_private.h"
#include "../Headers/EXTI_confige.h"
#include "../Headers/EXTI_interface.h"
static void (*EXTI_pvInt0CallBackFunc)(void) = 0;

void MEXTI_voidInitInt0(void)
{
	#if EXTI0_TRIGGER_MODE == EXTI_LOW_LEVEL
	MCUCR &= ~(1 << ISC00);
	MCUCR &= ~(1 << ISC01);

	#elif EXTI0_TRIGGER_MODE == EXTI_IOC
	MCUCR |=  (1 << ISC00);
	MCUCR &= ~(1 << ISC01);

	#elif EXTI0_TRIGGER_MODE == EXTI_FALLING_EDGE
	MCUCR &= ~(1 << ISC00);
	MCUCR |=  (1 << ISC01);

	#elif EXTI0_TRIGGER_MODE == EXTI_RISING_EDGE
	MCUCR |=  (1 << ISC00);
	MCUCR |=  (1 << ISC01);
	#endif

	GIFR |= (1 << 6);
}

void MEXTI_voidEnableInt0(void)
{
	GICR |= (1 << INT0);
}

void MEXTI_voidDisableInt0(void)
{
	GICR &= ~(1 << INT0);
}

void MEXTI_voidEnableGlobalInterrupt(void)
{
	SREG |= (1 << I_BIT);
}

void MEXTI_voidSetCallBackInt0(void (*Copy_pvNotificationFunc)(void))
{
	if (Copy_pvNotificationFunc != 0)
	{
		EXTI_pvInt0CallBackFunc = Copy_pvNotificationFunc;
	}
}

ISR(INT0_vect)
{
	if (EXTI_pvInt0CallBackFunc != 0)
	{
		EXTI_pvInt0CallBackFunc();
	}
}
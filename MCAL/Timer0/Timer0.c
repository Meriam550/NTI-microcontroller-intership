#include "std.h"
#include "bitmath.h"
#include "Timer0.h"

#define TOIE0   0
#define TOV0    0

#define CS00    0
#define CS01    1
#define CS02    2

static pf Timer0_OvfCallback = NULL;

void TIMER_Init(u8 Prescaler)
{
	TCCR0_REG &= 0xF8;
	TCCR0_REG |= (Prescaler & 0x07);
}

void TIMER_Stop(void)
{
	TCCR0_REG &= 0xF8;
}

void TIMER_SetInitialValue(u8 InitialValue)
{
	TCNT0_REG = InitialValue;
}

void TIMER_EnableOverflowInterrupt(void)
{
	SET_BIT(TIMSK_REG, TOIE0);
}

void TIMER_DisableOverflowInterrupt(void)
{
	CLEAR_BIT(TIMSK_REG, TOIE0);
}

void TIMER_SetOverflowCallback(pf Callback)
{
	Timer0_OvfCallback = Callback;
}

void __vector_11(void) __attribute__((signal, used));
void __vector_11(void)
{
	if(Timer0_OvfCallback != NULL)
	{
		Timer0_OvfCallback();
	}
}
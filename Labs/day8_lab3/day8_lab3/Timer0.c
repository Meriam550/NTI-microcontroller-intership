#include "std.h"
#include "bitmath.h"
#include "Timer0.h"

#define TOIE0   0
#define TOV0    0
#define OCIE0   1
#define OCF0    1

#define CS00    0
#define CS01    1
#define CS02    2

static pf Timer0_OvfCallback = NULL;
static pf Timer0_CmpCallback = NULL;

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

void TIMER_SetOCR0Value(u8 OCRValue)
{
	OCR0_REG = OCRValue;
}

void TIMER_EnableOverflowInterrupt(void)
{
	SET_BIT(TIMSK_REG, TOIE0);
}

void TIMER_DisableOverflowInterrupt(void)
{
	CLEAR_BIT(TIMSK_REG, TOIE0);
}

void TIMER_EnableCompareMatchInterrupt(void)
{
	SET_BIT(TIMSK_REG, OCIE0);
}

void TIMER_DisableCompareMatchInterrupt(void)
{
	CLEAR_BIT(TIMSK_REG, OCIE0);
}

void TIMER_SetOverflowCallback(pf Callback)
{
	Timer0_OvfCallback = Callback;
}

void TIMER_SetCompareMatchCallback(pf Callback)
{
	Timer0_CmpCallback = Callback;
}

// Overflow Interrupt Vector
void __vector_11(void) __attribute__((signal, used));
void __vector_11(void)
{
	if(Timer0_OvfCallback != NULL)
	{
		Timer0_OvfCallback();
	}
}

// Compare Match Interrupt Vector
void __vector_10(void) __attribute__((signal, used));
void __vector_10(void)
{
	if(Timer0_CmpCallback != NULL)
	{
		Timer0_CmpCallback();
	}
}
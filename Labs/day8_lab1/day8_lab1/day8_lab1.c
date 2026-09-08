#include "std.h"
#include "DIO_int.h"
#include "LED_interface.h"
#include "Timer0.h"
#include <avr/interrupt.h>

#define OVERFLOWS_PER_SECOND 61

LED_Type Led = {DPORTA, PIN0, ACTIVE_HIGH};
static volatile u8 overflow_counter = 0;

void Timer0_OvfCallback(void)
{
	overflow_counter++;
	if(overflow_counter >= OVERFLOWS_PER_SECOND)
	{
		LED_voidToggle(&Led);
		overflow_counter = 0;
	}
}

int main(void)
{
	LED_voidInit(&Led);
	
	TIMER_SetInitialValue(0);
	TIMER_SetOverflowCallback(Timer0_OvfCallback);
	TIMER_EnableOverflowInterrupt();
	
	sei();
	
	TIMER_Init(PRESCALER_1024);
	
	while(1)
	{
	}
	
	return 0;
}
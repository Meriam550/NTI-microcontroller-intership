

#define F_CPU 8000000UL
#include <util/delay.h>

#include "std.h"
#include "DIO_int.h"
#include "LED_interface.h"

int main(void)
{
    
    DIO_voidInitialization();

    LED_Type xLed = { DPORTA, PIN0, ACTIVE_HIGH };

    LED_voidInit(&xLed);

    while (1)
    {
        LED_voidToggle(&xLed);
        _delay_ms(500);
    }

    return 0;
}

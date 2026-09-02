
#define F_CPU 1000000
#include <util/delay.h>

#include "std.h"
#include "DIO_int.h"
#include "SevSegment.h"

int main(void)
{
    DIO_voidInitialization();

    while (1)
    {
        u8 digit;
        for (digit = 0; digit <= 9; digit++)
        {
            SevSegment_voidSetValue(digit);
            _delay_ms(1000);
        }
    }

    return 0;
}

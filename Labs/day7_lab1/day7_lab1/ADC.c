#include "std.h"
#include "bitmath.h"
#include "ADC.H"

#define REFS0   6
#define REFS1   7
#define ADEN    7
#define ADSC    6
#define ADIF    4
#define ADPS0   0
#define ADPS1   1
#define ADPS2   2

void ADC_Init(void)
{
    CLEAR_BIT(ADMUX, REFS1);
    SET_BIT(ADMUX, REFS0);
    
    SET_BIT(ADCSRA, ADPS2);
    SET_BIT(ADCSRA, ADPS1);
    CLEAR_BIT(ADCSRA, ADPS0);
    
    SET_BIT(ADCSRA, ADEN);
}

u16 ADC_Read(u8 channel)
{
    ADMUX &= 0xE0;
    ADMUX |= (channel & 0x07);
    
    SET_BIT(ADCSRA, ADSC);
    
    while(READ_BIT(ADCSRA, ADIF) == 0);
    
    SET_BIT(ADCSRA, ADIF);
    
    u16 result = ADCL;
    result |= (ADCH << 8);
    
    return result;
}
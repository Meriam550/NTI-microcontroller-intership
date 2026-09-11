#include "../../serv/std.h"
#include "../../serv/bitmath.h"
#include "ADC.h"

#define REFS0 6
#define REFS1 7
#define ADEN  7
#define ADSC  6
#define ADIF  4
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2

void ADC_Init(void)
{
    SET_BIT(ADMUX_Reg, REFS0);
    CLEAR_BIT(ADMUX_Reg, REFS1);
    
    SET_BIT(ADCSRA_Reg, ADPS2);
    SET_BIT(ADCSRA_Reg, ADPS1);
    CLEAR_BIT(ADCSRA_Reg, ADPS0);
    
    SET_BIT(ADCSRA_Reg, ADEN);
}

u16 ADC_Read(u8 channel)
{
    ADMUX_Reg &= 0xE0;
    ADMUX_Reg |= (channel & 0x07);
    
    SET_BIT(ADCSRA_Reg, ADSC);
    
    while(READ_BIT(ADCSRA_Reg, ADIF) == 0);
    
    SET_BIT(ADCSRA_Reg, ADIF);
    
    u16 result = ADCL_Reg;
    result |= (ADCH_Reg << 8);
    
    return result;
}
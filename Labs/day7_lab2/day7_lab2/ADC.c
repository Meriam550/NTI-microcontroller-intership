#include "std.h"
#include "bitmath.h"
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
    // Reference Voltage: AVCC with external capacitor at AREF pin
    SET_BIT(ADMUX_Reg, REFS0);
    CLEAR_BIT(ADMUX_Reg, REFS1);
    
    // ADC Prescaler = 64 (for 1MHz -> 15.6kHz, for 8MHz -> 125kHz, for 16MHz -> 250kHz)
    SET_BIT(ADCSRA_Reg, ADPS2);
    SET_BIT(ADCSRA_Reg, ADPS1);
    CLEAR_BIT(ADCSRA_Reg, ADPS0);
    
    // Enable ADC
    SET_BIT(ADCSRA_Reg, ADEN);
}

u16 ADC_Read(u8 channel)
{
    // Clear the channel selection bits (keep REFS0, REFS1, ADLAR)
    ADMUX_Reg &= 0xE0;
    ADMUX_Reg |= (channel & 0x07);
    
    // Start conversion
    SET_BIT(ADCSRA_Reg, ADSC);
    
    // Wait for conversion to finish (polling ADIF flag)
    while(READ_BIT(ADCSRA_Reg, ADIF) == 0);
    
    // Clear interrupt flag by writing 1 to it
    SET_BIT(ADCSRA_Reg, ADIF);
    
    // Read 10-bit result (ADCL must be read first)
    u16 result = ADCL_Reg;
    result |= ((u16)ADCH_Reg << 8);
    
    return result;
}
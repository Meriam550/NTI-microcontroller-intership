#include "std.h"
#include "ADC.h"
#include "bitmath.h"

//Set the AVcc pin =  5V for capacitor (ADCMUX REG)
#define REFS0 6
#define REFS1 7
//Set Power pin the ADC (ADCSRA REG)
#define ADEN 7
//Set pins of MCU clock speed = 125kHz using 8 Prescaler (ADCSRA REG)
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2

#define ADSC 6
#define ADIF 4




extern void ADC_Init (void){
	//Set the AVcc =  5V for capacitor (ADCMUX REG)
	SET_BIT(ADMUX_Reg, REFS0);
	CLEAR_BIT(ADMUX_Reg, REFS1);
	// MCU clock speed = 125kHz using 8 Prescaler (ADCSRA REG)
	SET_BIT(ADCSRA_Reg, ADPS0);
	SET_BIT(ADCSRA_Reg, ADPS1);
	CLEAR_BIT(ADCSRA_Reg, ADPS2);
	//Set Power on the ADC (ADCSRA REG)
	SET_BIT(ADCSRA_Reg, ADEN);
}


extern u16 ADC_Read(u8 channel)
{
	// Select the ADC channel (0-7)
	ADMUX_Reg &= 0xE0;  // Clear the first 5 bits
	ADMUX_Reg |= (channel & 0x07);  // Set the channel
	
	// Start conversion
	SET_BIT(ADCSRA_Reg, ADSC);
	
	// Wait for conversion to complete (polling)
	while(READ_BIT(ADCSRA_Reg, ADIF) == 0);
	
	// Clear the interrupt flag
	SET_BIT(ADCSRA_Reg, ADIF);
	
	// Read the 10-bit result (ADCL must be read first)
	u16 result = ADCL_Reg;
	result |= (ADCH_Reg << 8);
	
	return result;
}
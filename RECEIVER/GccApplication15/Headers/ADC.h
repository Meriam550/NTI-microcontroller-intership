#ifndef _ADC_H
#define _ADC_H
# include "Std_types.h"

#define ADMUX_Reg 	(*(volatile u8*)0x27) 	// ADC Multiplexer Register
//ADMUX PINS
#define REFS1 7
#define ADLAR 5
#define REFS0 6
#define MUX2 2
#define MUX1 1
#define MUX0 0

#define ADCH_Reg 	(*(volatile u8*)0x25) 		// ADC High Register
#define ADCL_Reg 	(*(volatile u8*)0x24) 		// ADC Low Register

#define ADCSRA_Reg 	(*(volatile u8*)0x26) 	// ADC Control And Status Register
//ADCSRA PINS
#define ADEN 7
#define ADSC 6
#define ADIF 4
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

void ADC_init();  // initialize the ADC
u16 ADC_Read(u8 channel); // takes the number of the pin that you want to read from and reads the value
#endif 
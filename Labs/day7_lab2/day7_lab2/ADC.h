#ifndef ADC_H_
#define ADC_H_

#include "std.h"

#define ADMUX_Reg   *((volatile u8*)0x27)
#define ADCSRA_Reg  *((volatile u8*)0x26)
#define ADCH_Reg    *((volatile u8*)0x25)
#define ADCL_Reg    *((volatile u8*)0x24)

#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7

void ADC_Init(void);
u16 ADC_Read(u8 channel);

#endif
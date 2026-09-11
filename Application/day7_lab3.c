#define F_CPU 1000000UL
#include "std.h"
#include "DIO_int.h"
#include "bitmath.h"
#include "ADC.h"
#include <util/delay.h>

#define YELLOW_LED  PIN0   
#define GREEN_LED   PIN1   
#define RED_LED     PIN2   
#define BUZZER      PIN3   

#define LM35_CHANNEL 0    

int main(void)
{
	u16 adcValue;
	float voltage_mV;
	float temperature;

	DIO_voidSetPortDirection(DPORTC, 0xFF);   //  LEDs + buzzer
	DIO_voidSetPortValue(DPORTC, 0x00);

	ADC_Init();

	while (1)
	{
		adcValue = ADC_Read(LM35_CHANNEL); 

		voltage_mV  = (adcValue * 5000.0) / 1024.0;   
		temperature = voltage_mV / 10.0;             

		DIO_voidSetPortValue(DPORTC, 0x00);   

		if (temperature < 20.0)
		{
			DIO_voidSetPinValue(DPORTC, GREEN_LED, HIGH);
		}
		else if (temperature <= 40.0)
		{
			DIO_voidSetPinValue(DPORTC, YELLOW_LED, HIGH);
		}
		else
		{
			DIO_voidSetPinValue(DPORTC, RED_LED, HIGH);
			DIO_voidSetPinValue(DPORTC, BUZZER, HIGH);
		}

		_delay_ms(500);
	}
}
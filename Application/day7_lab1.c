#include "std.h"
#include "ADC.h"
#include "DIO_int.h"

int main(void)
{
	
	DIO_voidSetPinDirection(DPORTA, PIN0, INPUT);
	
	
	DIO_voidSetPinDirection(DPORTC, PIN0, OUTPUT); // Red LED
	DIO_voidSetPinDirection(DPORTC, PIN1, OUTPUT); // Yellow LED
	DIO_voidSetPinDirection(DPORTC, PIN2, OUTPUT); // Green LED
	
	
	ADC_Init();
	
	while(1)
	{
		
		u16 adcValue = ADC_Read(ADC0);
		
		
		f32 voltage = (adcValue * 5.0) / 1023.0;
		
		
		DIO_voidSetPinValue(DPORTC, PIN0, LOW); // Red OFF
		DIO_voidSetPinValue(DPORTC, PIN1, LOW); // Yellow OFF
		DIO_voidSetPinValue(DPORTC, PIN2, LOW); // Green OFF
		
		
		if (voltage > 0.0 && voltage < 1.5)
		{
			DIO_voidSetPinValue(DPORTC, PIN0, HIGH); // Red LED ON
		}
		else if (voltage >= 1.5 && voltage < 3.0)
		{
			DIO_voidSetPinValue(DPORTC, PIN1, HIGH); // Yellow LED ON
		}
		else if (voltage >= 3.0)
		{
			DIO_voidSetPinValue(DPORTC, PIN2, HIGH); // Green LED ON
		}
	}
	
	return 0;
}
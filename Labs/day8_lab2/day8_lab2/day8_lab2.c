#include "std.h"
#include "DIO_int.h"
#include "ADC.h"
#include "Timer0.h"
#include <avr/interrupt.h>

#define LED_PORT    DPORTB
#define LED_PIN     PIN3  

// ADC channel for potentiometer
#define POT_CHANNEL 0

u16 adc_value = 0;


void Timer0_CompareMatchCallback()
{
	// Read current pin value
	u8 current_value = DIO_u8ReadPinValue(LED_PORT, LED_PIN);
	
	// Toggle the value
	u8 new_value = (current_value == HIGH) ? LOW : HIGH;
	
	// Set the new value
	DIO_voidSetPinValue(LED_PORT, LED_PIN, new_value);
}
int main(void)
{
	// Initialize DIO
	DIO_voidInitialization();
	
	// Set LED pin as output
	DIO_voidSetPinDirection(LED_PORT, LED_PIN, OUTPUT);
	
	// Initialize ADC
	ADC_Init();
	
	// Initialize Timer0 with prescaler 64 for appropriate frequency range
	TIMER_Init(PRESCALER_64);
	
	// Set compare match callback
	TIMER_SetCompareMatchCallback(Timer0_CompareMatchCallback);
	
	// Enable compare match interrupt
	TIMER_EnableCompareMatchInterrupt();
	
	// Enable global interrupts
	sei();
	
	while(1)
	{
		// Read potentiometer value (0-1023)
		adc_value = ADC_Read(POT_CHANNEL);
		
		
		u8 ocr_value = (u8)(adc_value >> 2);  
		
		// Update OCR0 register
		TIMER_SetOCR0Value(ocr_value);
		
		// Small delay for stability
		for(u32 i = 0; i < 1000; i++);
	}
	
	return 0;
}
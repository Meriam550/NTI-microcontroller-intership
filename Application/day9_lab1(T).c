/*
 * day9_lab1(T).c
 *
 * Created: 9/9/2026 7:56:11 PM
 * Author : Meriam
 */ 

#include "std.h"
#include "USART.h"
#include "DIO_int.h"

// Button connected to PD0 for sending data
#define SEND_BUTTON_PIN    PIN0
#define SEND_BUTTON_PORT   DPORTD

int main(void)
{
	// Set PD0 as input with internal pull-up enabled
	DIO_voidSetPinDirection(SEND_BUTTON_PORT, SEND_BUTTON_PIN, INPUT);
	DIO_voidSetPinValue(SEND_BUTTON_PORT, SEND_BUTTON_PIN, HIGH);  // Enable internal pull-up
	// Initialize button as input with pull-up
	DIO_voidSetPinDirection(SEND_BUTTON_PORT, SEND_BUTTON_PIN, INPUT);
	DIO_voidSetPinValue(SEND_BUTTON_PORT, SEND_BUTTON_PIN, HIGH);  // Enable pull-up
	
	// Initialize USART at 9600 baud
	USART_Init(9600);
	
	u8 counter = 1;
	
	while(1)
	{
		// Check if button is pressed (active low with pull-up)
		if(DIO_u8ReadPinValue(SEND_BUTTON_PORT, SEND_BUTTON_PIN) == LOW)
		{
			// Simple debounce delay
			u16 i;
			for(i = 0; i < 5000; i++);
			
			// Confirm button still pressed
			if(DIO_u8ReadPinValue(SEND_BUTTON_PORT, SEND_BUTTON_PIN) == LOW)
			{
				// Send number (1-4, then cycle back)
				USART_SendChar(counter);
				
				// Increment counter (1, 2, 3, 4, 1, 2, ...)
				counter++;
				if(counter > 4)
				{
					counter = 1;
				}
				
				// Wait for button release
				while(DIO_u8ReadPinValue(SEND_BUTTON_PORT, SEND_BUTTON_PIN) == LOW);
			}
		}
	}
	
	
}
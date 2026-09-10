/*
 * day9_lab1(R).c
 *
 * Created: 9/9/2026 8:00:26 PM
 * Author : Meriam
 */ 

#include "std.h"
#include "USART.h"
#include "DIO_int.h"
#include "LED_interface.h"

// LED Configuration
LED_Type Led1 = {DPORTC, PIN0, ACTIVE_HIGH};
LED_Type Led2 = {DPORTC, PIN1, ACTIVE_HIGH};
LED_Type Led3 = {DPORTC, PIN2, ACTIVE_HIGH};
LED_Type Led4 = {DPORTC, PIN3, ACTIVE_HIGH};

int main(void)
{
	// Initialize LEDs
	LED_voidInit(&Led1);
	LED_voidInit(&Led2);
	LED_voidInit(&Led3);
	LED_voidInit(&Led4);
	
	// Initialize USART at 9600 baud
	USART_Init(9600);
	
	while(1)
	{
		// Wait for data from transmitter
		u8 received_data = USART_Get_Char();
		
		// Toggle corresponding LED based on received number
		switch(received_data)
		{
			case 1:  // Changed from '1' to 1
			LED_voidToggle(&Led1);
			break;
			case 2:  // Changed from '2' to 2
			LED_voidToggle(&Led2);
			break;
			case 3:  // Changed from '3' to 3
			LED_voidToggle(&Led3);
			break;
			case 4:  // Changed from '4' to 4
			LED_voidToggle(&Led4);
			break;
			default:
			// Ignore invalid data
			break;
		}
	}
	
	
}
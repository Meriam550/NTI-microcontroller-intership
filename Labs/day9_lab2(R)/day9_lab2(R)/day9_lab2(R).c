/*
 * day9_lab2(R).c - SPI Slave Receiver
 *
 * Created: 9/9/2026
 * Author : Meriam
 */

#include "std.h"
#include "SPI.h"
#include "DIO_int.h"
#include "LED_interface.h"

// SPI Slave Pins on PORTB
#define SPI_SS_PIN         PIN4
#define SPI_MOSI_PIN       PIN5
#define SPI_MISO_PIN       PIN6
#define SPI_SCK_PIN        PIN7
#define SPI_PORT           DPORTB

// LED Configuration on PORTC
LED_Type Led1 = {DPORTC, PIN0, ACTIVE_HIGH};
LED_Type Led2 = {DPORTC, PIN1, ACTIVE_HIGH};
LED_Type Led3 = {DPORTC, PIN2, ACTIVE_HIGH};
LED_Type Led4 = {DPORTC, PIN3, ACTIVE_HIGH};

int main(void)
{
	// 1. Initialize LEDs
	LED_voidInit(&Led1);
	LED_voidInit(&Led2);
	LED_voidInit(&Led3);
	LED_voidInit(&Led4);
	
	// 2. Configure SPI Slave Hardware Pins (PORTB)
	DIO_voidSetPinDirection(SPI_PORT, SPI_SS_PIN, INPUT);     // SS as Input
	DIO_voidSetPinDirection(SPI_PORT, SPI_MOSI_PIN, INPUT);   // MOSI as Input
	DIO_voidSetPinDirection(SPI_PORT, SPI_MISO_PIN, OUTPUT);  // MISO as Output
	DIO_voidSetPinDirection(SPI_PORT, SPI_SCK_PIN, INPUT);    // SCK as Input
	
	// 3. Initialize SPI as Slave, Mode 0
	SPI_InitSlave(0);
	SPI_Enable();
	
	while(1)
	{
		// Wait and receive data from Master
		u8 received_data = SPI_SlaveReceive();
		
		// Toggle corresponding LED based on received number
		switch(received_data)
		{
			case 1:
				LED_voidToggle(&Led1);
				break;
			case 2:
				LED_voidToggle(&Led2);
				break;
			case 3:
				LED_voidToggle(&Led3);
				break;
			case 4:
				LED_voidToggle(&Led4);
				break;
			default:
				// Ignore any unknown data
				break;
		}
	}
	
	return 0;
}
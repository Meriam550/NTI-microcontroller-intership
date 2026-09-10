/*
 * day9_lab2(T).c - SPI Master Transmitter
 *
 * Created: 9/9/2026
 * Author : Meriam
 */ 

#include "std.h"
#include "SPI.h"
#include "DIO_int.h"

// Button connected to PD0 for sending data
#define SEND_BUTTON_PIN    PIN0
#define SEND_BUTTON_PORT   DPORTD

// SPI Master Pins on PORTB
#define SPI_SS_PIN         PIN4
#define SPI_MOSI_PIN       PIN5
#define SPI_MISO_PIN       PIN6
#define SPI_SCK_PIN        PIN7
#define SPI_PORT           DPORTB

int main(void)
{
	// 1. Initialize button as input with internal pull-up
	DIO_voidSetPinDirection(SEND_BUTTON_PORT, SEND_BUTTON_PIN, INPUT);
	DIO_voidSetPinValue(SEND_BUTTON_PORT, SEND_BUTTON_PIN, HIGH);
	
	// 2. Configure SPI Master Hardware Pins (PORTB)
	DIO_voidSetPinDirection(SPI_PORT, SPI_SS_PIN, OUTPUT);    // SS as Output
	DIO_voidSetPinDirection(SPI_PORT, SPI_MOSI_PIN, OUTPUT);  // MOSI as Output
	DIO_voidSetPinDirection(SPI_PORT, SPI_MISO_PIN, INPUT);   // MISO as Input
	DIO_voidSetPinDirection(SPI_PORT, SPI_SCK_PIN, OUTPUT);   // SCK as Output
	
	// Set SS high initially (Slave deselected / inactive)
	DIO_voidSetPinValue(SPI_PORT, SPI_SS_PIN, HIGH);
	
	// 3. Initialize SPI as Master, Mode 0, Prescaler 16
	SPI_InitMaster(0, SPI_PRESCALER_16);
	SPI_Enable();
	
	u8 counter = 1;
	
	while(1)
	{
		// Check if button is pressed (Active Low)
		if(DIO_u8ReadPinValue(SEND_BUTTON_PORT, SEND_BUTTON_PIN) == LOW)
		{
			// Debounce delay
			u16 i;
			for(i = 0; i < 5000; i++);
			
			// Confirm button is still pressed
			if(DIO_u8ReadPinValue(SEND_BUTTON_PORT, SEND_BUTTON_PIN) == LOW)
			{
				// Select Slave (SS Low)
				DIO_voidSetPinValue(SPI_PORT, SPI_SS_PIN, LOW);
				
				// Send counter value (1 to 4)
				SPI_SendByte(counter);
				
				// Deselect Slave (SS High)
				DIO_voidSetPinValue(SPI_PORT, SPI_SS_PIN, HIGH);
				
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
	
	return 0;
}
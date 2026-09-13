#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "Headers/Std_types.h"
#include "Headers/Bit_Math.h"
#include "Headers/DIO.h"
#include "Headers/LCD.H"
#include "Headers/keypad.h"
#include "Headers/USART.h"

int main(void)
{
	// Initialize Peripherals
	LCD_init();
	KEYPAD_init();
	USART_Init(9600);
	
	const u8 correctpass[3] = {'1', '2', '3'};
	u8 attempts = 0;
	
	for (attempts = 0; attempts < 3; attempts++)
	{
		LCD_SendCommand(0b00000001); // Clear LCD
		_delay_ms(2);
		LCD_SendString((u8 *)"Enter door pass:");
		GoToXY(0, 1);
		u8 entered[3];
		
		for (u8 enterednum = 0; enterednum < 3; enterednum++)
		{
			u8 storing = KEYPAD_keypressed();
			while (storing == '\0')
			{
				storing = KEYPAD_keypressed();
			}
			
			// Clear button ('C') handling
			if (storing == 'C')
			{
				_delay_ms(150);
				LCD_SendCommand(0b00000001);
				GoToXY(0, 0);
				LCD_SendString((u8 *)"Enter door pass:");
				GoToXY(0, 1);
				enterednum = 0;
				_delay_ms(100);
				continue;
			}
			
			entered[enterednum] = storing;
			LCD_sendChar('*'); // Mask password entry
			_delay_ms(50);
		}
		
		LCD_SendCommand(0b00000001);
		GoToXY(0, 0);
		
		// Validate Password
		if (entered[0] == correctpass[0] &&
		entered[1] == correctpass[1] &&
		entered[2] == correctpass[2])
		{
			LCD_SendString((u8 *)"Door Opened");
			GoToXY(0, 1);
			LCD_SendString((u8 *)"Welcome!");
			
			// Send Authorized signal to Receiver MCU
			USART_SendChar('1');
			break;
		}
		else
		{
			LCD_SendString((u8 *)"Wrong pass!");
		}
		_delay_ms(500);
	}
	
	// If 3 incorrect attempts reached
	if (attempts >= 3)
	{
		LCD_SendCommand(0b00000001);
		GoToXY(0, 0);
		LCD_SendString((u8 *)"Access Denied!");
		GoToXY(0, 1);
		LCD_SendString((u8 *)"Alarm Triggered!");
		
		// Send Alarm trigger signal to Receiver MCU
		USART_SendChar('2');
	}
	
	while (1)
	{
		
	}
}

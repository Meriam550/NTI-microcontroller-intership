/*
 * day9_I2C_S.c
 *
 * Created: 9/12/2026 1:17:18 AM
 * Author : Meriam
 */ 

#define F_CPU 1000000UL

#include "std.h"
#include "bitmath.h"
#include "DIO_int.h"
#include "LCD.h"
#include "i2c.h"
#include <util/delay.h>

#define SLAVE_ADDRESS 0x01
int main(void)
{
	u8 received_data = 0;

	
	_delay_ms(100);

	
	LCD_init();

	
	I2C_InitSlave(SLAVE_ADDRESS);

	
	LCD_SendCommand(0x01); // Clear screen
	_delay_ms(2);
	GoToXY(0, 0);
	LCD_SendString((u8*)"LDR Node Monitor");
	GoToXY(0, 1);
	LCD_SendString((u8*)"Waiting I2C...");

	while (1)
	{
		
		if (I2C_SlaveReceiveByte(&received_data) == 1)
		{
			GoToXY(0, 1);
			if (received_data == 'D')
			{
				LCD_SendString((u8*)"Status: DARK  ");
			}
			else if (received_data == 'B')
			{
				LCD_SendString((u8*)"Status: BRIGHT");
			}
		}
	}

	return 0;
}
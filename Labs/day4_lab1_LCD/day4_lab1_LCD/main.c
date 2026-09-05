/*
 * day4_lab1_LCD.c
 *
 * Created: 9/3/2026 7:39:37 PM
 * Author : Meriam
 */ 

#define F_CPU 1000000UL
#include "std.h"
#include "DIO_int.h"
#include "LCD.h"
#include <util/delay.h>


int main(void)
{
	LCD_init();
	
	 
    /* Replace with your application code */
    while (1) 
    {
		LCD_sendChar('M');
		_delay_ms(500);
		
		 LCD_GoToXY(1, 5);
		LCD_SendString ("Meriam");
		_delay_ms(500);		 
		
		LCD_SendCommand(0x01);
		_delay_ms(500);
		
				
		
		
		
    }
}


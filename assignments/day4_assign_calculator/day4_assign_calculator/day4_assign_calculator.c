#include "std.h"
#include "keypad.h"
#include "LCD.h"
#include <util/delay.h>

int main(void)
{
	keypad_init();
	LCD_init();

	while (1)
	{
		s8 result;

		LCD_SendCommand(0x01);           
		GoToXY(0, 0);
		LCD_SendString((u8*)"Enter:");   

		result = keypad_calc();         

		GoToXY(0, 1);                   
		LCD_SendString((u8*)"= ");
		LCD_voidWriteNumber(result);    

		_delay_ms(2000);                
	}
}
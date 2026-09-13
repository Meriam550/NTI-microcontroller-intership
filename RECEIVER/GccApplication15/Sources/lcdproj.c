#include "../Headers/LCD.h"
#include "../Headers/Std_types.h"
#include <util/delay.h>

//RS PIN 0 RW PIN1 ENABLE PIN2
	
void LCD_init(void)
{
	DIO_voidSetPinDirection(PORTB, PIN0, OUTPUT); //CP
	DIO_voidSetPinDirection(PORTB, PIN1, OUTPUT); //CP
	DIO_voidSetPinDirection(PORTB, PIN2, OUTPUT); //CP
	DIO_voidSetPortDirection(PORTA, 0B11111111); //DP

	_delay_ms(40);

	LCD_SendCommand(0b00111000);
	_delay_us(39);
	LCD_SendCommand(0b00001100);
	_delay_us(39);

	LCD_SendCommand(0b00000001);
	_delay_ms(2);
}
	
void LCD_SendCommand(u8 command){
	DIO_voidSetPinValue(PORTB,PIN0, LOW); //CP
	DIO_voidSetPinValue(PORTB,PIN1, LOW); //CP
	
	DIO_voidSetPortValue(PORTA, command); //DP
	
    DIO_voidSetPinValue(PORTB, PIN2, HIGH); //CP
    _delay_ms(1);
    DIO_voidSetPinValue(PORTB, PIN2, LOW); //CP
}
void LCD_sendChar(u8 Data){
	DIO_voidSetPinValue(PORTB, PIN0, HIGH);  //CT
	DIO_voidSetPinValue(PORTB, PIN1, LOW);   //CT
	
	DIO_voidSetPortValue(PORTA, Data);  //DP     	

	DIO_voidSetPinValue(PORTB, PIN2, HIGH); //DP
	_delay_ms(2);
	DIO_voidSetPinValue(PORTB, PIN2, LOW); //DP
}
void LCD_SendString(u8 *str){
	u8 i = 0;
	while (str[i]  != '\0')
	{
		LCD_sendChar(str[i]);
		i++;
	}
}
	
void GoToXY(u8 x, u8 y)
{
	u8 Local_u8Address = 0;
	
	if (y == 0)
	{
		Local_u8Address = x; 
	}
	else if (y == 1)
	{
		Local_u8Address = x + 0x40; 
	}

	LCD_SendCommand(0x80 | Local_u8Address);
}

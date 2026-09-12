#include "DIO_int.h"
#include "LCD.h"
#include <util/delay.h>

void LCD_init(void){
	DIO_voidSetPortDirection(DPORTB, OUTPUT);
	DIO_voidSetPortDirection(DPORTD, OUTPUT);
	DIO_voidSetPortValue(DPORTB, LOW);
	DIO_voidSetPortValue(DPORTD, LOW);
	
	_delay_ms(30);
	LCD_SendCommand(0x38);  // Set to 8-bit mode
	_delay_ms(1);
	LCD_SendCommand(0x0C);  // Turn display ON, cursor OFF
	_delay_ms(1);
	LCD_SendCommand(0x01);  // Clear screen
	_delay_ms(2);
	LCD_SendCommand(0x06);  // Entry mode: auto-increment
}

void LCD_sendChar(u8 Data){
	DIO_voidSetPinValue(DPORTB, PIN0, HIGH); // RS: Send data
	DIO_voidSetPinValue(DPORTB, PIN1, LOW);  // RW: Write
	
	DIO_voidSetPortValue(DPORTD, Data);
	
	DIO_voidSetPinValue(DPORTB, PIN2, HIGH); 
	_delay_ms(1);
	DIO_voidSetPinValue(DPORTB, PIN2, LOW);  
	_delay_ms(2);
}

void LCD_SendCommand(u8 command){
	DIO_voidSetPinValue(DPORTB, PIN0, LOW);  // RS: Command
	DIO_voidSetPinValue(DPORTB, PIN1, LOW);  // RW: Write
	DIO_voidSetPortValue(DPORTD, command);
	
	DIO_voidSetPinValue(DPORTB, PIN2, HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(DPORTB, PIN2, LOW);
	_delay_ms(2);	   
}

void LCD_SendString(u8 *str){
	while(*str != '\0'){
		LCD_sendChar(*str);
		str++;
	}	
}

void GoToXY(u8 x, u8 y)
{
	u8 address;
	switch (y) {
		case 0: address = 0x00 + x; break;
		case 1: address = 0x40 + x; break;
		default: address = 0x00 + x; break;
	}
	LCD_SendCommand(0x80 | address);
}

void LCD_voidWriteNumber(s32 num)
{
	u8 buffer[12];
	u8 i = 0, isNegative = 0, j, temp;

	if (num < 0) { isNegative = 1; num = -num; }

	if (num == 0) {
		buffer[i++] = '0';
	} else {
		while (num > 0) {
			buffer[i++] = (num % 10) + '0';
			num /= 10;
		}
	}
	if (isNegative) buffer[i++] = '-';

	for (j = 0; j < i / 2; j++) {
		temp = buffer[j];
		buffer[j] = buffer[i - 1 - j];
		buffer[i - 1 - j] = temp;
	}
	buffer[i] = '\0';

	LCD_SendString(buffer);
}
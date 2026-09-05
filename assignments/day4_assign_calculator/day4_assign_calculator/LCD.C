

#include "std.h"
#include "DIO_int.h"
#include "LCD.h"
#include <util/delay.h>




 
 
 
 void LCD_init(void){
	 
	  DIO_voidSetPortDirection(DPORTC, OUTPUT);
	  _delay_ms(2000);
	  DIO_voidSetPortDirection(DPORTD, OUTPUT);
	  _delay_ms(2000);
	  DIO_voidSetPortValue(DPORTC, LOW);
	  _delay_ms(2000);
	  DIO_voidSetPortValue(DPORTD, LOW);
	  _delay_ms(2000);
	  

	  
	  
	  
 }
 
 void LCD_sendChar(u8 Data){
	 
	  DIO_voidSetPinValue(DPORTC, PIN0, HIGH);//RS:Send data
	  DIO_voidSetPinValue(DPORTC, PIN1, LOW);//RW:Write
	  
	  DIO_voidSetPortValue(DPORTD,  Data);
	  
	  DIO_voidSetPinValue(DPORTC, PIN2, HIGH); 
	  _delay_ms(1);
	  DIO_voidSetPinValue(DPORTC, PIN2, LOW);  

	  
	  _delay_ms(2);
	 
 }
 
 void LCD_SendCommand(u8 command){
	 
	   DIO_voidSetPinValue(DPORTC, PIN0, LOW);
	   DIO_voidSetPinValue(DPORTC, PIN1, LOW);
	   DIO_voidSetPortValue(DPORTD, command);
	   
	  DIO_voidSetPinValue(DPORTC, PIN2, HIGH);
	  _delay_ms(1);
	  DIO_voidSetPinValue(DPORTC, PIN2, LOW);

	  
	  _delay_ms(2);	   
 }
 
void LCD_SendString (u8 *str){
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
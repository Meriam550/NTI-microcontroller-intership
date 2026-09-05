

#include "std.h"
#include "DIO_int.h"
#include "LCD.h"
#include <util/delay.h>




 
 
 
 void LCD_init(void){
	  DIO_voidSetPinDirection(DPORTC, PIN0, OUTPUT);
	 _delay_ms(10);
	  DIO_voidSetPinDirection(DPORTC, PIN1, OUTPUT);
	  _delay_ms(10);
	  DIO_voidSetPinDirection(DPORTC, PIN2, OUTPUT);
	  _delay_ms(10);	  	 
	  DIO_voidSetPinDirection(DPORTD, PIN0, OUTPUT);
	  _delay_ms(10);
	  DIO_voidSetPinDirection(DPORTD, PIN1, OUTPUT);
	  _delay_ms(10);
	  DIO_voidSetPinDirection(DPORTD, PIN2, OUTPUT);
	  _delay_ms(10);
	  DIO_voidSetPinDirection(DPORTD, PIN3, OUTPUT);
	  _delay_ms(10);
	  DIO_voidSetPinDirection(DPORTD, PIN4, OUTPUT);
	  _delay_ms(10);
	  DIO_voidSetPinDirection(DPORTD, PIN5, OUTPUT);
	  _delay_ms(10);
	  DIO_voidSetPinDirection(DPORTD, PIN6, OUTPUT);
	  _delay_ms(10);
	  DIO_voidSetPinDirection(DPORTD, PIN7, OUTPUT);
	  _delay_ms(10);	  	    	  	  	  	  
	  DIO_voidSetPinValue(DPORTC, PIN0, LOW);
	 _delay_ms(10);
	  DIO_voidSetPinValue(DPORTC, PIN1, LOW);
	  _delay_ms(10);
	  DIO_voidSetPinValue(DPORTC, PIN2, LOW);
	  _delay_ms(10);	  	 
	  DIO_voidSetPinValue(DPORTD, PIN0, LOW);
	  _delay_ms(10); 
	  DIO_voidSetPinValue(DPORTD, PIN1, LOW);
	  _delay_ms(10);
	  DIO_voidSetPinValue(DPORTD, PIN2, LOW);
	  _delay_ms(10);
	  DIO_voidSetPinValue(DPORTD, PIN3, LOW);
	  _delay_ms(10);
	  DIO_voidSetPinValue(DPORTD, PIN4, LOW);
	  _delay_ms(10);
	  DIO_voidSetPinValue(DPORTD, PIN5, LOW);
	  _delay_ms(10);
	  DIO_voidSetPinValue(DPORTD, PIN6, LOW);
	  _delay_ms(10);
	  DIO_voidSetPinValue(DPORTD, PIN7, LOW);
	  _delay_ms(10);	  	  	  	  	  	  	  
	
	 LCD_SendCommand(0x38);  // 8-bit mode, 2 lines
	 _delay_ms(10);
	 LCD_SendCommand(0x0C);  // Display ON
	 _delay_ms(10);
	 LCD_SendCommand(0x01);  // Clear display
	 _delay_ms(20);
	 LCD_SendCommand(0x06);  // Cursor increment
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
		_delay_ms(100);
	    str++;
    }	
}

void LCD_GoToXY(u8 line, u8 col)
{
	
	if (line > 1 || col > 15)
	{
		return;
	}
	u8 address = 0;

	
	if (line == 0)
	{
		address = 0x80 + col; 
	}
	else if (line == 1)
	{
		address = 0xC0 + col; 
	}

	
	LCD_SendCommand(address);
}
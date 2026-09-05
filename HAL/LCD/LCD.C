

//#include "std.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "LCD.h"
#include <util/delay.h>




 
 
 
 void LCD_init(void){
	 
	  DIO_voidSetPortDirection(DPORTC, OUTPUT);
	  DIO_voidSetPortDirection(DPORTD, OUTPUT);
	  DIO_voidSetPortValue(DPORTC, LOW);
	  DIO_voidSetPortValue(DPORTD, LOW);
	  
	  LCD_SendCommand(0x38);  // Set to 8-bit mode
	  LCD_SendCommand(0x0C);  // Turn display ON
	  LCD_SendCommand(0x01);  // Clear screen
	  LCD_SendCommand(0x06);
	  
	  
	  
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
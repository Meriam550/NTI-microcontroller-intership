#ifndef LCD_H_
#define LCD_H_

//#include "std.h"



//init
void LCD_init(void);

//char
void LCD_sendChar(u8 Data);

//send command
void LCD_SendCommand(u8 command);

//Send String
void LCD_SendString (u8 *str);
 
 void GoToXY(u8 x,u8 y);
 
 void LCD_voidWriteNumber(s32 num);
 
 
 
 #endif
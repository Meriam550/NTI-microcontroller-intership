#ifndef _LCD_H_
#define _LCD_H_
#include "Std_types.h"
#include <avr/io.h>
#include "Std_types.h"
#include "Bit_Math.h"
#include "DIO.h"



//init
void LCD_init();
 
//char
void LCD_sendChar(u8 Data);
 
//send command
void LCD_SendCommand(u8 command);
 
//Send String
void LCD_SendString (u8 *str);

void GoToXY(u8 x, u8 y);

void LCD_voidWriteNumber(s32 num);






#endif
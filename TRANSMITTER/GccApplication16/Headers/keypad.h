#ifndef _KEYPAD_H_
#define _KEYPAD_H_
#include "Std_types.h"
#include <avr/io.h>
#include "Std_types.h"
#include "Bit_Math.h"
#include "DIO.h"
#include "LCD.H"



void KEYPAD_init(void);
char KEYPAD_getPressedKey(void);



#endif
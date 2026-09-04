/*
 * day4_lab2_keypad.c
 *
 * Created: 9/3/2026 10:37:35 PM
 * Author : Meriam
 */ 

#include "keypad.h"
#include "SevSegment.h"
#include "std.h"
#include "DIO_int.h"


int main(void)
{
	u8 key = NO_KEY;
	keypad_init();
	SevSegment_voidInit();
  
	
    /* Replace with your application code */
    while (1) 
    {
		key = GetPressedKey();


if (key != NO_KEY)
{
u8 numeric_value;

switch (key)
{
	case '0': numeric_value = 0; break;
	case '1': numeric_value = 1; break;
	case '2': numeric_value = 2; break;
	case '3': numeric_value = 3; break;
	case '4': numeric_value = 4; break;
	case '5': numeric_value = 5; break;
	case '6': numeric_value = 6; break;
	case '7': numeric_value = 7; break;
	case '8': numeric_value = 8; break;
	case '9': numeric_value = 9; break;
	default:  ; 
}

SevSegment_voidSetValue(numeric_value);	

}		
		
		
		
	
		
		
		
		
		
		

		
    }
	
}


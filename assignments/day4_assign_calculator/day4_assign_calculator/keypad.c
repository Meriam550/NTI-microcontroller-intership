#include "std.h"
#include "bitmath.h"
#include "DIO_int.h"
#include "keypad.h"
#include <util/delay.h>

void keypad_init(void) {
	
	DIO_voidSetPinDirection(DPORTA, PIN0, INPUT);
	DIO_voidSetPinDirection(DPORTA, PIN1, INPUT);
	DIO_voidSetPinDirection(DPORTA, PIN2, INPUT);
	DIO_voidSetPinDirection(DPORTA, PIN3, INPUT);
	
	
	DIO_voidSetPinDirection(DPORTB, PIN0, OUTPUT);
	DIO_voidSetPinDirection(DPORTB, PIN1, OUTPUT);
	DIO_voidSetPinDirection(DPORTB, PIN2, OUTPUT);
	DIO_voidSetPinDirection(DPORTB, PIN3, OUTPUT);
	
	
	DIO_voidSetPinValue(DPORTA, PIN0, HIGH);
	DIO_voidSetPinValue(DPORTA, PIN1, HIGH);
	DIO_voidSetPinValue(DPORTA, PIN2, HIGH);
	DIO_voidSetPinValue(DPORTA, PIN3, HIGH);
	
	
	DIO_voidSetPinValue(DPORTB, PIN0, HIGH);
	DIO_voidSetPinValue(DPORTB, PIN1, HIGH);
	DIO_voidSetPinValue(DPORTB, PIN2, HIGH);
	DIO_voidSetPinValue(DPORTB, PIN3, HIGH);
}

u8 Keypad_u8GetPressedKeyBlocking(void) {
	u8 key = NO_KEY;
	while (key == NO_KEY) {
		key = GetPressedKey();
	}
	return key;
}

u8 GetPressedKey(void) {

	u8 key = NO_KEY;
	u8 row, col;
	
	u8 arr[4][4] = {
		{  '/',         '9',         '8',         '7'  },
		{  '*',         '6',         '5',         '4'  },
		{  '-',         '3',         '2',         '1'  },
		{  '+',         '=',         '0',         'C'  }
	};
	
	for (col = 0; col < 4; col++) {
		
		DIO_voidSetPortValue(DPORTB, ~(1 << col));
		
		for (row = 0; row < 4; row++) {
			if (DIO_u8ReadPinValue(DPORTA, row) == LOW) {
				_delay_ms(20);  
				if (DIO_u8ReadPinValue(DPORTA, row) == LOW) {
					
					while (DIO_u8ReadPinValue(DPORTA, row) == LOW);
					DIO_voidSetPortValue(DPORTB, 0xFF);  
					return arr[row][col];
				}
			}
		}
	}
	
	DIO_voidSetPortValue(DPORTB, 0xFF);   
	return NO_KEY;   
}




u8 keypad_calc(void){
	u8 op1_char = Keypad_u8GetPressedKeyBlocking();
	u8 op2_char = Keypad_u8GetPressedKeyBlocking();
	u8 operator = Keypad_u8GetPressedKeyBlocking();
	u8 op1 = op1_char - '0';
	u8 op2 = op2_char - '0';
	u8 result = 0;

	switch(operator){
		case '/':
		if(op2 == 0){
			return 0;
			} else {
			result = op1/op2;
		}
		break;

		case '*':
		result = op1*op2;
		break;

		case '-':
		result = op1-op2;
		break;

		case '+':
		result = op1+op2;
		break;

		default:
		return 0;  
	}
	return result;
}
#include "std.h"
#include "bitmath.h"
#include "DIO_int.h"
#include "keypad.h"
#include <util/delay.h>

void keypad_init(void) {
	// Fixed: Set all row pins as INPUT with pull-up
	DIO_voidSetPinDirection(DPORTA, PIN0, INPUT);
	DIO_voidSetPinDirection(DPORTA, PIN1, INPUT);
	DIO_voidSetPinDirection(DPORTA, PIN2, INPUT);
	DIO_voidSetPinDirection(DPORTA, PIN3, INPUT);
	
	// Fixed: Set all column pins as OUTPUT
	DIO_voidSetPinDirection(DPORTB, PIN0, OUTPUT);
	DIO_voidSetPinDirection(DPORTB, PIN1, OUTPUT);
	DIO_voidSetPinDirection(DPORTB, PIN2, OUTPUT);
	DIO_voidSetPinDirection(DPORTB, PIN3, OUTPUT);
	
	// Fixed: Enable pull-ups on rows (HIGH)
	DIO_voidSetPinValue(DPORTA, PIN0, HIGH);
	DIO_voidSetPinValue(DPORTA, PIN1, HIGH);
	DIO_voidSetPinValue(DPORTA, PIN2, HIGH);
	DIO_voidSetPinValue(DPORTA, PIN3, HIGH);
	
	// Fixed: Set all columns HIGH initially
	DIO_voidSetPinValue(DPORTB, PIN0, HIGH);
	DIO_voidSetPinValue(DPORTB, PIN1, HIGH);
	DIO_voidSetPinValue(DPORTB, PIN2, HIGH);
	DIO_voidSetPinValue(DPORTB, PIN3, HIGH);
}

u8 GetPressedKey(void) {
	// Fixed: Initialize to NO_KEY instead of confusing KEY_PRESSED
	u8 key = NO_KEY;
	u8 row, col;
	
	u8 arr[4][4] = {
		{  '/',         '9',         '8',         '7'  },
		{  '*',         '6',         '5',         '4'  },
		{  '-',         '3',         '2',         '1'  },
		{  '+',         '=',         '0',         'C'  }
	};
	
	for (col = 0; col < 4; col++) {
		// Fixed: Set current column LOW, ensure others are HIGH
		DIO_voidSetPortValue(DPORTB, ~(1 << col));
		
		for (row = 0; row < 4; row++) {
			if (DIO_u8ReadPinValue(DPORTA, row) == LOW) {
				_delay_ms(20);  // Debounce delay
				if (DIO_u8ReadPinValue(DPORTA, row) == LOW) {
					// Wait for key release
					while (DIO_u8ReadPinValue(DPORTA, row) == LOW);
					DIO_voidSetPortValue(DPORTB, 0xFF);  // Reset columns
					return arr[row][col];
				}
			}
		}
	}
	
	DIO_voidSetPortValue(DPORTB, 0xFF);  // Reset columns
	return NO_KEY;  // Fixed: Return NO_KEY (0) instead of 0
}
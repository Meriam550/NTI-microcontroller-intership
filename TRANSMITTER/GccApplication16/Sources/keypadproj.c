#include "../Headers/Std_Types.h"
#include "../Headers/Bit_Math.h"
#include <avr/io.h>
#include <util/delay.h>
#include "../Headers/keypad.h"

void KEYPAD_init(void) {
	 DIO_voidSetPinDirection(PORTC , PIN0 ,INPUT);
	 DIO_voidSetPinDirection(PORTC , PIN1 ,INPUT);
	 DIO_voidSetPinDirection(PORTC , PIN2 ,INPUT);
	DIO_voidSetPinDirection(PORTC , PIN3 ,INPUT);
	 DIO_voidSetPinDirection(PORTC , PIN4 ,OUTPUT);
	 DIO_voidSetPinDirection(PORTC , PIN5 ,OUTPUT);
	 DIO_voidSetPinDirection(PORTC , PIN6 ,OUTPUT);
	 DIO_voidSetPinDirection(PORTC , PIN7 ,OUTPUT);
	 DIO_voidSetPortValue(PORTC,0B11111111);
}

char KEYPAD_keypressed(void) {
	const u8 keypad_matrix[4][4] = {{'7', '8', '9', '/'},{'4', '5', '6', '*'},{'1', '2', '3', '-'},{'C', '0', '=', '+'}};
    u8 rows [4]={PIN0 , PIN1 , PIN2 , PIN3 };
	u8 colomns[4]={PIN4 , PIN5 , PIN6 , PIN7 };
		
		for (u8 column=0 ; column<4 ; column++){
	 for (u8 j =0 ; j<4; j++ ){
		 DIO_voidSetPinValue(PORTC, colomns[j], HIGH);
	 }
	   DIO_voidSetPinValue(PORTC, colomns[column], LOW);

	for ( u8 row = 0; row < 4; row++) {
		if (( DIO_u8ReadPinValue(PORTC,rows[row]))==LOW){
			 while (DIO_u8ReadPinValue(PORTC, rows[row]) == LOW) // polling 
			return keypad_matrix [row][column];}
	}
		}

	return '\0';
}
#include "std.h"
#include "bitmath.h"
#include "DIO_int.h"

int main(void)
{
	/* Configure Switch Pins as INPUT */
	 DIO_voidSetPortDirection(DPORTA, INPUT);
	 /* Enable Internal Pull-Up Resistors for Switches */
	 DIO_voidSetPortValue(DPORTA, HIGH);
	 /* Configure LED Pins as OUTPUT */
	 DIO_voidSetPortDirection(DPORTC, OUTPUT);
	 /* Turn OFF all LEDs initially */
	 DIO_voidSetPortValue(DPORTC, LOW);
	

	while (1)
	{
		/* Check Master Switch (PA3) */
		if (DIO_u8ReadPinValue(DPORTA, PIN3) == LOW)
		{
			DIO_voidSetPinValue(DPORTC, PIN0, HIGH);
			DIO_voidSetPinValue(DPORTC, PIN1, HIGH);
			DIO_voidSetPinValue(DPORTC, PIN2, HIGH);
		}
		else
		{
			/* Individual Switches */
			if (DIO_u8ReadPinValue(DPORTA, PIN0) == LOW) {
				DIO_voidSetPinValue(DPORTC, PIN0, HIGH);
			} else {
				DIO_voidSetPinValue(DPORTC, PIN0, LOW);
			}

			if (DIO_u8ReadPinValue(DPORTA, PIN1) == LOW) {
				DIO_voidSetPinValue(DPORTC, PIN1, HIGH);
			} else {
				DIO_voidSetPinValue(DPORTC, PIN1, LOW);
			}

			if (DIO_u8ReadPinValue(DPORTA, PIN2) == LOW) {
				DIO_voidSetPinValue(DPORTC, PIN2, HIGH);
			} else {
				DIO_voidSetPinValue(DPORTC, PIN2, LOW);
			}
		}
	}

	return 0;
}










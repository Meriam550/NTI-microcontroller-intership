/*
 * day8_lab3.c
 *
 * Created: 9/8/2026 10:16:27 PM
 * Author : Meriam
 */ 

#define F_CPU 1000000UL
#include "SERVO.h"
#include <util/delay.h>

int main(void)
{
	SERVO_Init();
	
	while(1)
	{
		for(u8 angle = 180; angle <= 180; angle += 10)
		{
			SERVO_SetAngle(angle);
			_delay_ms(500);
		}
		
		for(u8 angle = 180; angle >= 0; angle -= 10)
		{
			SERVO_SetAngle(angle);
			_delay_ms(500);
		}
	}
	
	return 0;
}

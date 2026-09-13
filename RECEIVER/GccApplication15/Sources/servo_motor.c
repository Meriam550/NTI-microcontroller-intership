#include "../Headers/servo_motor.h"

void    ServoMotor_Init(void)
{
	CLR_BIT(TCCR1A_REG,0);//WGM10
	SET_BIT(TCCR1A_REG,1);//WGM11
	SET_BIT(TCCR1B_REG,3);//WGM12
	SET_BIT(TCCR1B_REG,4);//WGM13
	//enable PWM mode with ICR1 as TOP insead of 10^16
	
	CLR_BIT(TCCR1A_REG,6);//COM1A0
	SET_BIT(TCCR1A_REG,7);//COM1A1
	//Clear on compare match,set at TOP ->PIN(DP5)==OC1A
	
	CLR_BIT(TCCR1A_REG,4);//COM1B0
	SET_BIT(TCCR1A_REG,5);//COM1B1
	//Clear on compare match,set at TOP ->PIN(DP4)==OC1B

	CLR_BIT(TCCR1B_REG,0);//CS10
	SET_BIT(TCCR1B_REG,1);//CS11
	CLR_BIT(TCCR1B_REG,2);//CS12
	//prescaler = 8

	ICR1H_REG = (2499>>8);
	ICR1L_REG = (2499);
	//make top(ICR1) ==2499
	//periodic time=20ms ,frequency=50Hz
}


void ServoMotor_OCA1_Angle(u8 angle)
{
	u8 OCR_Value;
	OCR_Value = 188 +(angle * 62) / 180;
	OCR1AH_REG = (OCR_Value >> 8);
	OCR1AL_REG = OCR_Value;
}

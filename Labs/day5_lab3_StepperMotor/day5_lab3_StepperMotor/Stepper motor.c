
#define F_CPU 1000000UL
#include "std.h"
#include "bitmath.h"
#include "DIO_int.h"
#include "Stepper motor.h"
#include <util/delay.h>

#define STEPPER_PORT  DPORTC

#define STEPPER_FULL_STEP  0
#define STEPPER_HALF_STEP  1

static const u8 FullStepSeq[4][4] = {
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 1},
	{1, 0, 0, 1}
};

static const u8 HalfStepSeq[8][4] = {
	{1, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 1},
	{0, 0, 0, 1},
	{1, 0, 0, 1}
};

static u8 fullStepIndex = 0;
static u8 halfStepIndex = 0;

static void ApplyCoilState(const u8 *coilState)
{
	DIO_voidSetPinValue(STEPPER_PORT, PIN0, coilState[0]);
	DIO_voidSetPinValue(STEPPER_PORT, PIN1, coilState[1]);
	DIO_voidSetPinValue(STEPPER_PORT, PIN2, coilState[2]);
	DIO_voidSetPinValue(STEPPER_PORT, PIN3, coilState[3]);
}

void Stepper_voidInit(void)
{
	DIO_voidSetPinDirection(STEPPER_PORT, PIN0, OUTPUT);
	DIO_voidSetPinDirection(STEPPER_PORT, PIN1, OUTPUT);
	DIO_voidSetPinDirection(STEPPER_PORT, PIN2, OUTPUT);
	DIO_voidSetPinDirection(STEPPER_PORT, PIN3, OUTPUT);


	DIO_voidSetPinValue(STEPPER_PORT, PIN0, LOW);
	DIO_voidSetPinValue(STEPPER_PORT, PIN1, LOW);
	DIO_voidSetPinValue(STEPPER_PORT, PIN2, LOW);
	DIO_voidSetPinValue(STEPPER_PORT, PIN3, LOW);

	fullStepIndex = 0;
	halfStepIndex = 0;
}

void Stepper_voidStepFullStep(u8 direction)
{
	if (direction == STEPPER_CW) {
		fullStepIndex = (fullStepIndex + 1) % 4;
		} else {
		fullStepIndex = (fullStepIndex == 0) ? 3 : (fullStepIndex - 1);
	}

	ApplyCoilState(FullStepSeq[fullStepIndex]);
	_delay_ms(STEPPER_STEP_DELAY_MS);
}

void Stepper_voidStepHalfStep(u8 direction)
{
	if (direction == STEPPER_CW) {
		halfStepIndex = (halfStepIndex + 1) % 8;
		} else {
		halfStepIndex = (halfStepIndex == 0) ? 7 : (halfStepIndex - 1);
	}

	ApplyCoilState(HalfStepSeq[halfStepIndex]);
	_delay_ms(STEPPER_STEP_DELAY_MS);
}

void Stepper_voidRotateSteps(u8 mode, u8 direction, u16 numSteps)
{
	u16 i;
	for (i = 0; i < numSteps; i++) {
		if (mode == STEPPER_FULL_STEP) {
			Stepper_voidStepFullStep(direction);
			} else {
			Stepper_voidStepHalfStep(direction);
		}
	}
}
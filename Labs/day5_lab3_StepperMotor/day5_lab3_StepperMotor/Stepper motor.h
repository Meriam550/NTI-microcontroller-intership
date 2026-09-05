#ifndef STEPPER_H
#define STEPPER_H

#include "std.h"

// Direction
#define STEPPER_CW   0
#define STEPPER_CCW  1


#define STEPPER_STEP_DELAY_MS  1000

void Stepper_voidInit(void);


void Stepper_voidStepFullStep(u8 direction);


void Stepper_voidStepHalfStep(u8 direction);


void Stepper_voidRotateSteps(u8 mode, u8 direction, u16 numSteps);

#endif
#include "std.h"
#include "Stepper motor.h"

int main(void)
{
	Stepper_voidInit();

	while (1)
	{

		Stepper_voidRotateSteps(0, STEPPER_CCW, 100);
	}
}
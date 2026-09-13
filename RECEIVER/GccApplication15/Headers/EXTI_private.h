#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#include "Std_types.h"

#define MCUCR   (*((volatile u8*)0x55))
#define MCUCSR  (*((volatile u8*)0x54))
#define GICR    (*((volatile u8*)0x5B))
#define GIFR    (*((volatile u8*)0x5A))
#define SREG    (*((volatile u8*)0x5F))

#define ISC00   0
#define ISC01   1
#define ISC10   2
#define ISC11   3

#define INT1    7
#define INT0    6
#define INT2    5

#define I_BIT   7

#define EXTI_LOW_LEVEL      0
#define EXTI_IOC            1
#define EXTI_FALLING_EDGE   2
#define EXTI_RISING_EDGE    3

#endif
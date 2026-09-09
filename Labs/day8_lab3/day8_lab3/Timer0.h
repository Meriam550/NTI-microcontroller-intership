#ifndef TIMER_H_
#define TIMER_H_

#include "std.h"

#define NO_CLOCK        0
#define PRESCALER_1      1
#define PRESCALER_8      2
#define PRESCALER_64     3
#define PRESCALER_256    4
#define PRESCALER_1024   5
#define EXT_FALLING      6
#define EXT_RISING       7

#define TCNT0_REG       *((volatile u8*)0x52)
#define TCCR0_REG       *((volatile u8*)0x53)
#define OCR0_REG        *((volatile u8*)0x5C)
#define TIMSK_REG       *((volatile u8*)0x59)
#define TIFR_REG        *((volatile u8*)0x58)

void TIMER_Init(u8 Prescaler);
void TIMER_Start(void);
void TIMER_Stop(void);
void TIMER_SetInitialValue(u8 InitialValue);
void TIMER_SetOCR0Value(u8 OCRValue);
void TIMER_EnableOverflowInterrupt(void);
void TIMER_DisableOverflowInterrupt(void);
void TIMER_EnableCompareMatchInterrupt(void);
void TIMER_DisableCompareMatchInterrupt(void);
void TIMER_SetOverflowCallback(pf Callback);
void TIMER_SetCompareMatchCallback(pf Callback);

#endif
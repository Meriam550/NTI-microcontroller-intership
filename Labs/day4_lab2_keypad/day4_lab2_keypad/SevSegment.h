

#ifndef SEVSEGMENT_H
#define SEVSEGMENT_H

#include "std.h"


#define SEVSEG_PORT     DPORTC

#define SEVSEG_TYPE     LOW     /* 0: Common Cathode | 1: Common Anode */


void SevSegment_voidSetValue(u8 Num);
void SevSegment_voidInit(void);





#endif 

#ifndef KEYPAD_H
#define KEYPAD_H

#include "std.h"

#define NO_KEY  LOW


void keypad_init(void);
u8 GetPressedKey(void);




#endif
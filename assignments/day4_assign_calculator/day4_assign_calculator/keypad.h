#ifndef KEYPAD_H
#define KEYPAD_H

#include "std.h"

#define NO_KEY  LOW


void keypad_init(void);
u8 GetPressedKey(void);
u8 keypad_calc(void);
u8 Keypad_u8GetPressedKeyBlocking(void);






#endif
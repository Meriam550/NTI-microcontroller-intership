

#include "std.h"
#include "bitmath.h"
#include "DIO_int.h"
#include "SevSegment.h"


static const u8 SevSeg_Numbers[10] =
{
    
    0x3F,   
    0x06,   
    0x5B,   
    0x4F,  
    0x66,  
    0x6D,  
    0x7D,   
    0x07,   
    0x7F,  
    0x6F    
};


void SevSegment_voidSetValue(u8 Num)
{
    if (Num > 9)
        return;    

    u8 pattern = SevSeg_Numbers[Num];

#if (SEVSEG_TYPE == 1)
    pattern = ~pattern;
#endif

    DIO_voidSetPortValue(SEVSEG_PORT, pattern);
}

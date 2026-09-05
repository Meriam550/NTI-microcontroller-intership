

#include "std.h"
#include "bitmath.h"
#include "DIO_int.h"
#include "SevSegment.h"



static const u8 SevSeg_Numbers[10] =
{
    
    0x3F,   /* 0: 0b00111111 */
    0x06,   /* 1: 0b00000110 */
    0x5B,   /* 2: 0b01011011 */
    0x4F,   /* 3: 0b01001111 */
    0x66,   /* 4: 0b01100110 */
    0x6D,   /* 5: 0b01101101 */
    0x7D,   /* 6: 0b01111101 */
    0x07,   /* 7: 0b00000111 */
    0x7F,   /* 8: 0b01111111 */
    0x6F    /* 9: 0b01101111 */
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







void SevSegment_voidInit(void){
	DIO_voidSetPortDirection(DPORTC, 0xFF);   
	DIO_voidSetPortValue(DPORTC, LOW);
}


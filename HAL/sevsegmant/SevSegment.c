/*
 * SevSegment.c
 *
 * HAL driver for a single 7-segment display.
 * All port writes go through DIO_voidSetPortValue() — no raw register access.
 */

#include "../../serv/std.h"
#include "../../serv/bitmath.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "SevSegment.h"

/*
 * Common-cathode bitmasks for digits 0–9.
 *
 * Bit position → segment:
 *   bit0=a  bit1=b  bit2=c  bit3=d  bit4=e  bit5=f  bit6=g
 *
 *       a
 *      ---
 *   f |   | b
 *      -g-
 *   e |   | c
 *      ---
 *       d
 */
static const u8 SevSeg_Numbers[10] =
{
    /*  gfedcba */
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

/* ── SevSegment_voidSetValue ─────────────────────────────────────────────
 * Drive digit Num (0–9) on SEVSEG_PORT.
 * Bitmask is inverted at compile time for common-anode displays.
 */
void SevSegment_voidSetValue(u8 Num)
{
    if (Num > 9)
        return;     /* ignore out-of-range input */

    u8 pattern = SevSeg_Numbers[Num];

#if (SEVSEG_TYPE == 1)
    /* Common Anode: segments are active-LOW, so flip all bits */
    pattern = ~pattern;
#endif

    DIO_voidSetPortValue(SEVSEG_PORT, pattern);
}

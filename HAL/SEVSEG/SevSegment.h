/*
 * SevSegment.h
 *
 * HAL driver for a single common-cathode or common-anode 7-segment display.
 * Digits are driven port-wide through the MCAL DIO layer (no direct register access).
 *
 * Segment-to-pin mapping (assumed):
 *   PA0=a  PA1=b  PA2=c  PA3=d  PA4=e  PA5=f  PA6=g  PA7=dp (unused)
 */

#ifndef SEVSEGMENT_H
#define SEVSEGMENT_H

#include "../../serv/std.h"

/* ── Hardware Configuration ─────────────────────────────────────────────── */

/* Port the display data lines are connected to (DPORTA / DPORTB / DPORTC / DPORTD) */
#define SEVSEG_PORT     DPORTA

/* Display type:
 *   0 → Common Cathode  (HIGH = segment ON)
 *   1 → Common Anode    (LOW  = segment ON, bits inverted automatically)
 */
#define SEVSEG_TYPE     0       /* 0: Common Cathode | 1: Common Anode */

/* ── Public API ─────────────────────────────────────────────────────────── */

/* Drive a decimal digit (0–9) onto the configured port. */
void SevSegment_voidSetValue(u8 Num);

#endif /* SEVSEGMENT_H */

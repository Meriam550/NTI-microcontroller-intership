#ifndef _DIO_INT_H
#define _DIO_INT_H

#define OUTPUT 1
#define INPUT 0

#define LOW	0
#define HIGH	1

#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7

#define DPORTA  0
#define DPORTB	1
#define DPORTC	2
#define DPORTD	3

void DIO_voidInitialization(void);

void DIO_voidSetPinDirection(u8 PortID, u8 PinID, u8 Direction);
void DIO_voidSetPinValue(u8 PortID, u8 PinID, u8 Value);

void DIO_voidSetPortValue(u8 PortID, u8 Value);
void DIO_voidSetPortDirection(u8 PortID, u8 Direction);

u8 DIO_u8ReadPinValue(u8 PortID, u8 PinID);

#endif
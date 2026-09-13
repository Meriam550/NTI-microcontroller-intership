#ifndef _DIO_H_
#define _DIO_H_
#include "Std_types.h"
#include <avr/io.h>
#include "Std_types.h"
#include "Bit_Math.h"

#define OUTPUT 1
#define INPUT  0

#define LOW  0
#define HIGH 1

#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7

#define PORTA  0
#define PORTB  1
#define PORTC  2
#define PORTD  3

//--------------------------------------------------

void DIO_voidIntialization(void);

void DIO_voidSetPinDirection(u8 PortID, u8 PinID, u8 Direction);

void DIO_voidSetPinValue(u8 PortID, u8 PinID, u8 Value);

u8   DIO_u8ReadPinValue(u8 PortID, u8 PinID);

void DIO_voidSetPortDirection(u8 PortID, u8 Direction);

void DIO_voidSetPortValue(u8 PortID, u8 Value);

u8   DIO_u8ReadPortValue(u8 PortID);

//--------------------------------------------------


// Helper macros for two-stage preprocessor token concatenation
//#define CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)  0b##b7##b6##b5##b4##b3##b2##b1##b0
//#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)         CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)

// Assembled 8-bit port direction macros from DIO_config.h
//#define DIO_PORTA_DIRECTION  CONC(DIO_PORTA_PIN7_DIR, DIO_PORTA_PIN6_DIR, DIO_PORTA_PIN5_DIR, DIO_PORTA_PIN4_DIR, DIO_PORTA_PIN3_DIR, DIO_PORTA_PIN2_DIR, DIO_PORTA_PIN1_DIR, DIO_PORTA_PIN0_DIR)
//#define DIO_PORTB_DIRECTION  CONC(DIO_PORTB_PIN7_DIR, DIO_PORTB_PIN6_DIR, DIO_PORTB_PIN5_DIR, DIO_PORTB_PIN4_DIR, DIO_PORTB_PIN3_DIR, DIO_PORTB_PIN2_DIR, DIO_PORTB_PIN1_DIR, DIO_PORTB_PIN0_DIR)
//#define DIO_PORTC_DIRECTION  CONC(DIO_PORTC_PIN7_DIR, DIO_PORTC_PIN6_DIR, DIO_PORTC_PIN5_DIR, DIO_PORTC_PIN4_DIR, DIO_PORTC_PIN3_DIR, DIO_PORTC_PIN2_DIR, DIO_PORTC_PIN1_DIR, DIO_PORTC_PIN0_DIR)
//#define DIO_PORTD_DIRECTION  CONC(DIO_PORTD_PIN7_DIR, DIO_PORTD_PIN6_DIR, DIO_PORTD_PIN5_DIR, DIO_PORTD_PIN4_DIR, DIO_PORTD_PIN3_DIR, DIO_PORTD_PIN2_DIR, DIO_PORTD_PIN1_DIR, DIO_PORTD_PIN0_DIR)


//Port A, B, C, D --> DDR, PORT, PIN Register

/** Comment: Port A Registers*/
#define DDRA      *((volatile u8 *)0x3A)
#define DPORTA     *((volatile u8 *)0x3B)
#define PINA      *((volatile u8 *)0x39)

/** Comment: Port B Registers*/
#define DDRB      *((volatile u8 *)0x37)
#define DPORTB     *((volatile u8 *)0x38)
#define PINB      *((volatile u8 *)0x36)

/** Comment: Port C Registers*/
#define DDRC      *((volatile u8 *)0x34)
#define DPORTC     *((volatile u8 *)0x35)
#define PINC      *((volatile u8 *)0x33)

/** Comment: Port D Registers*/
#define DDRD      *((volatile u8 *)0x31)
#define DPORTD     *((volatile u8 *)0x32)
#define PIND      *((volatile u8 *)0x30)

#endif
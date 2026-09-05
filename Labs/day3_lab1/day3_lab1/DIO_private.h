#ifndef _DIO_PRIVATE_H
#define _DIO_PRIVATE_H
#include "DIO_config.h"

// --- Register Definitions ---
#define DDRA *((volatile u8*) 0x3A)
#define PORTA *((volatile u8*) 0x3B)
#define PINA *((volatile u8*) 0x39)

#define DDRB *((volatile u8*) 0x37)
#define PORTB *((volatile u8*) 0x38)
#define PINB *((volatile u8*) 0x36)

#define DDRC *((volatile u8*) 0x34)
#define PORTC *((volatile u8*) 0x35)
#define PINC *((volatile u8*) 0x33)

#define DDRD *((volatile u8*) 0x31)
#define PORTD *((volatile u8*) 0x32)
#define PIND *((volatile u8*) 0x30)

#define DIO_PORTA_DIRECTION ((DIO_PORTA_PIN7_DIR << 7) | \
(DIO_PORTA_PIN6_DIR << 6) | \
(DIO_PORTA_PIN5_DIR << 5) | \
(DIO_PORTA_PIN4_DIR << 4) | \
(DIO_PORTA_PIN3_DIR << 3) | \
(DIO_PORTA_PIN2_DIR << 2) | \
(DIO_PORTA_PIN1_DIR << 1) | \
(DIO_PORTA_PIN0_DIR << 0))

#define DIO_PORTB_DIRECTION ((DIO_PORTB_PIN7_DIR << 7) | \
(DIO_PORTB_PIN6_DIR << 6) | \
(DIO_PORTB_PIN5_DIR << 5) | \
(DIO_PORTB_PIN4_DIR << 4) | \
(DIO_PORTB_PIN3_DIR << 3) | \
(DIO_PORTB_PIN2_DIR << 2) | \
(DIO_PORTB_PIN1_DIR << 1) | \
(DIO_PORTB_PIN0_DIR << 0))

#define DIO_PORTC_DIRECTION ((DIO_PORTC_PIN7_DIR << 7) | \
(DIO_PORTC_PIN6_DIR << 6) | \
(DIO_PORTC_PIN5_DIR << 5) | \
(DIO_PORTC_PIN4_DIR << 4) | \
(DIO_PORTC_PIN3_DIR << 3) | \
(DIO_PORTC_PIN2_DIR << 2) | \
(DIO_PORTC_PIN1_DIR << 1) | \
(DIO_PORTC_PIN0_DIR << 0))

#define DIO_PORTD_DIRECTION ((DIO_PORTD_PIN7_DIR << 7) | \
(DIO_PORTD_PIN6_DIR << 6) | \
(DIO_PORTD_PIN5_DIR << 5) | \
(DIO_PORTD_PIN4_DIR << 4) | \
(DIO_PORTD_PIN3_DIR << 3) | \
(DIO_PORTD_PIN2_DIR << 2) | \
(DIO_PORTD_PIN1_DIR << 1) | \
(DIO_PORTD_PIN0_DIR << 0))

#endif

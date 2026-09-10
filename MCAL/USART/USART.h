#ifndef USART_H_
#define USART_H_

#include "Bit_Math.h"
#include "Std_types.h"

// USART Register Addresses for ATmega32
#define UDR     *((volatile u8*)0x2C)  // USART Data Register holds data in box for writing {transmitting} and reading {receiving}
#define UCSRA   *((volatile u8*)0x2B)  // USART Control and Status Register A
#define UCSRB   *((volatile u8*)0x2A)  // controls/enables USART functions
#define UCSRC   *((volatile u8*)0x40)  // USART Control and Status Register C
#define UBRRL   *((volatile u8*)0x29)  // USART Baud Rate Register Low
#define UBRRH   *((volatile u8*)0x2D)  // USART Baud Rate Register High

// UCSRA Register Bit Positions
#define RXC     7    // USART Receive checking[if there is unread message RXC=1 ,if not RXC=0}
#define TXC     6    // USART Transmit Complete{if Transmission Completely finished then TXC=1}
#define UDRE    5    // USART Data Register Empty{the transmit buffer is empty UDRE = 1,if not UDRE = 0}
#define FE      4    // Frame Error{if something wrong FE=0}
#define DOR     3    // Data OverRun{DOR=1 means received data arrived faster than the software/receiver could handle it.}
#define PE      2    // Parity Error{If no. of 1's don't match PE = 1}
#define U2X     1    // Double Transmission Speed{U2X controls whether asynchronous USART uses normal or double speed.}
#define MPCM    0    // Multi-Processor Communication Mode

// UCSRB Register Bit Positions
#define RXCIE   7    //enable interrupt when RXC occurs.
#define TXCIE   6    //enable interrupt when TXC occurs.
#define UDRIE   5    //enable interrupt when UDRE occurs.
#define RXEN    4    // RXEN = Receiver Enable {if RXEN = 1 USART receiver is ON}
#define TXEN    3    // TXEN = Transmitter Enable{If TXEN = 1 the transmitter is ON.}
#define UCSZ2   2    // Character Size (bit 2)
#define RXB8    1    // Receive Data Bit 8
#define TXB8    0    // Transmit Data Bit 8

// UCSRC Register Bit Positions
#define URSEL   7    // Register Select (must be 1 to access UCSRC)
#define UMSEL   6    // USART Mode Select
#define UPM1    5    // Parity Mode (bit 1)
#define UPM0    4    // Parity Mode (bit 0)
#define USBS    3    // Stop Bit Select
#define UCSZ1   2    // Character Size (bit 1)
#define UCSZ0   1    // Character Size (bit 0)
#define UCPOL   0    // Clock Polarity

// Character Size Options
#define USART_5_BIT    0
#define USART_6_BIT    1
#define USART_7_BIT    2
#define USART_8_BIT    3
#define USART_9_BIT    7

// Parity Mode Options
#define PARITY_DISABLED   0
#define PARITY_EVEN       2
#define PARITY_ODD        3

// Stop Bit Options
#define STOP_BIT_1        0
#define STOP_BIT_2        1

// USART Mode Options
#define USART_ASYNC_MODE  0
#define USART_SYNC_MODE   1

// Function Prototypes
void USART_Init(u32 baud_rate);
void USART_SendChar(u8 data);
u8 USART_Get_Char(void);
void USART_SendString(const u8 *str);
void USART_ReceiveString(u8 *str);

#endif /* USART_H_ */
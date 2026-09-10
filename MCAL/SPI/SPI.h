#ifndef SPI_H_
#define SPI_H_

#include "std.h"

// SPI Register Addresses for ATmega32
#define SPCR    *((volatile u8*)0x2D)  // SPI Control Register
#define SPSR    *((volatile u8*)0x2E)  // SPI Status Register
#define SPDR    *((volatile u8*)0x2F)  // SPI Data Register

// SPCR Register Bit Positions
#define SPIE    7    // SPI Interrupt Enable
#define SPE     6    // SPI Enable
#define DORD    5    // Data Order (0=MSB first, 1=LSB first)
#define MSTR    4    // Master/Slave Select (0=Slave, 1=Master)
#define CPOL    3    // Clock Polarity
#define CPHA    2    // Clock Phase
#define SPR1    1    // SPI Clock Rate Select 1
#define SPR0    0    // SPI Clock Rate Select 0

// SPSR Register Bit Positions
#define SPIF    7    // SPI Interrupt Flag
#define WCOL    6    // Write Collision Flag
#define SPI2X   0    // Double SPI Speed Bit

// Prescaler Options (for Master mode)
#define SPI_PRESCALER_4     0
#define SPI_PRESCALER_16    1
#define SPI_PRESCALER_64    2
#define SPI_PRESCALER_128   3

// Function Prototypes
void SPI_InitMaster(u8 mode, u8 prescaler);
void SPI_InitSlave(u8 mode);
void SPI_Enable(void);
void SPI_Disable(void);
u8 SPI_Transceive(u8 data);
void SPI_SendByte(u8 data);
u8 SPI_ReceiveByte(void);
u8 SPI_SlaveReceive(void);

#endif /* SPI_H_ */
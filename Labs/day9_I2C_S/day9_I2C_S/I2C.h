#ifndef I2C_H_
#define I2C_H_

#include "std.h"

//  TWI Register Definitions
#define TWBR_Reg    *((volatile u8*)0x20)  // TWI Bit Rate Register
#define TWSR_Reg    *((volatile u8*)0x21)  // TWI Status Register
#define TWAR_Reg    *((volatile u8*)0x22)  // TWI Address Register (Slave)
#define TWDR_Reg    *((volatile u8*)0x23)  // TWI Data Register
#define TWCR_Reg    *((volatile u8*)0x56)  // TWI Control Register

// TWCR Bit Positions 
#define TWINT   7   // Interrupt Flag
#define TWEA    6   // Enable Acknowledge
#define TWSTA   5   // START Condition
#define TWSTO   4   // STOP Condition
#define TWWC    3   // Write Collision Flag
#define TWEN    2   // TWI Enable
#define TWIE    0   // Interrupt Enable


void I2C_InitSlave(u8 slave_address);
u8   I2C_SlaveReceiveByte(u8* pData);
u8   I2C_GetStatus(void);

#endif
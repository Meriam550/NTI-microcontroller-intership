#ifndef I2C_H_
#define I2C_H_

#include "std.h"

// ------------------- TWI Register Definitions -------------------
#define TWBR_Reg    *((volatile u8*)0x20)  // TWI Bit Rate Register
#define TWSR_Reg    *((volatile u8*)0x21)  // TWI Status Register
#define TWAR_Reg    *((volatile u8*)0x22)  // TWI Address Register (Slave)
#define TWDR_Reg    *((volatile u8*)0x23)  // TWI Data Register
#define TWCR_Reg    *((volatile u8*)0x56)  // TWI Control Register

// ------------------- TWCR Bit Positions -------------------------
#define TWINT   7   // Interrupt Flag (Clear by writing 1)
#define TWEA    6   // Enable Acknowledge
#define TWSTA   5   // START Condition
#define TWSTO   4   // STOP Condition
#define TWWC    3   // Write Collision Flag
#define TWEN    2   // TWI Enable
#define TWIE    0   // Interrupt Enable

// ------------------- TWSR Bit Positions & Status ----------------
#define TWPS0   0   // Prescaler Bit 0
#define TWPS1   1   // Prescaler Bit 1

// Status Codes (TWSR & 0xF8)
#define I2C_START_SUCCESS          0x08  // START transmitted
#define I2C_REP_START_SUCCESS      0x10  // Repeated START transmitted
#define I2C_MT_SLA_W_ACK           0x18  // Master Transmit: SLA+W transmitted, ACK received
#define I2C_MT_DATA_ACK            0x28  // Master Transmit: Data transmitted, ACK received
#define I2C_MR_SLA_R_ACK           0x40  // Master Receive: SLA+R transmitted, ACK received
#define I2C_MR_DATA_ACK            0x50  // Master Receive: Data received, ACK returned
#define I2C_MR_DATA_NACK           0x58  // Master Receive: Data received, NACK returned
#define I2C_SR_SLA_W_ACK           0x60  // Slave Receive: Own SLA+W received, ACK returned
#define I2C_SR_DATA_ACK            0x80  // Slave Receive: Data received, ACK returned
#define I2C_SR_STOP                0xA0  // Slave Receive: STOP condition received

// ------------------- Function Prototypes ------------------------
// Master Functions
void I2C_InitMaster(void);
void I2C_Start(void);
void I2C_RepeatedStart(void);
void I2C_Stop(void);
void I2C_SendSlaveAddressWithWrite(u8 slave_address);
void I2C_SendSlaveAddressWithRead(u8 slave_address);
void I2C_WriteData(u8 data);
u8   I2C_ReadDataWithACK(void);
u8   I2C_ReadDataWithNACK(void);

// Slave Functions
void I2C_InitSlave(u8 slave_address);
u8   I2C_SlaveListen(void);
u8   I2C_SlaveReceive(void);

// Status Function
u8   I2C_GetStatus(void);

#endif /* I2C_H_ */
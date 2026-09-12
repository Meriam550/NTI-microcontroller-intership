#include "std.h"
#include "bitmath.h"
#include "i2c.h"

// ------------------- Master Functions -------------------

void I2C_InitMaster(void)
{
	// Set SCL frequency = 100kHz for F_CPU = 1MHz or 8MHz (Prescaler = 1)
	// SCL_Freq = F_CPU / (16 + 2(TWBR) * Prescaler)
	TWBR_Reg = 0x02;
	
	// Set Prescaler to 1 (TWPS1 = 0, TWPS0 = 0)
	CLEAR_BIT(TWSR_Reg, TWPS0);
	CLEAR_BIT(TWSR_Reg, TWPS1);
	
	// Enable TWI
	SET_BIT(TWCR_Reg, TWEN);
}

void I2C_Start(void)
{
	// Clear TWINT, Set TWSTA (Start), Enable TWI
	TWCR_Reg = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	// Wait for TWINT flag to be set (transmission complete)
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
}

void I2C_RepeatedStart(void)
{
	TWCR_Reg = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
}

void I2C_Stop(void)
{
	// Clear TWINT, Set TWSTO (Stop), Enable TWI
	TWCR_Reg = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void I2C_SendSlaveAddressWithWrite(u8 slave_address)
{
	// 7-bit slave address shifted left, R/W bit = 0 (Write)
	TWDR_Reg = (slave_address << 1);
	
	// Clear TWINT and Enable TWI to start transmission
	TWCR_Reg = (1 << TWINT) | (1 << TWEN);
	
	// Wait for completion
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
}

void I2C_SendSlaveAddressWithRead(u8 slave_address)
{
	// 7-bit slave address shifted left, R/W bit = 1 (Read)
	TWDR_Reg = (slave_address << 1) | 0x01;
	
	TWCR_Reg = (1 << TWINT) | (1 << TWEN);
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
}

void I2C_WriteData(u8 data)
{
	TWDR_Reg = data;
	TWCR_Reg = (1 << TWINT) | (1 << TWEN);
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
}

u8 I2C_ReadDataWithACK(void)
{
	TWCR_Reg = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
	return TWDR_Reg;
}

u8 I2C_ReadDataWithNACK(void)
{
	TWCR_Reg = (1 << TWINT) | (1 << TWEN);
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
	return TWDR_Reg;
}

// ------------------- Slave Functions -------------------

void I2C_InitSlave(u8 slave_address)
{
	// Set 7-bit Slave Address in TWAR
	TWAR_Reg = (slave_address << 1);
	
	// Enable TWI, Enable Acknowledge bit (TWEA)
	TWCR_Reg = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
}

u8 I2C_SlaveListen(void)
{
	while (1)
	{
		// Wait until addressed by a master
		while (READ_BIT(TWCR_Reg, TWINT) == 0);
		
		u8 status = I2C_GetStatus();
		if (status == I2C_SR_SLA_W_ACK)
		{
			return 1; // Addressed with SLA+W
		}
	}
}

u8 I2C_SlaveReceive(void)
{
	// Clear TWINT and keep TWEA set to acknowledge incoming data
	TWCR_Reg = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	
	// Wait until data is received
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
	
	return TWDR_Reg;
}

u8 I2C_GetStatus(void)
{
	// Mask lower 3 prescaler bits to extract 5-bit status code
	return (TWSR_Reg & 0xF8);
}
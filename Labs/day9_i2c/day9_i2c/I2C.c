#include "std.h"
#include "bitmath.h"
#include "i2c.h"

// Master Functions 

void I2C_InitMaster(void)
{
	
	TWBR_Reg = 0x02;
	
	CLEAR_BIT(TWSR_Reg, TWPS0);
	CLEAR_BIT(TWSR_Reg, TWPS1);
	

	SET_BIT(TWCR_Reg, TWEN);
}

void I2C_Start(void)
{
	
	TWCR_Reg = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
}

void I2C_RepeatedStart(void)
{
	TWCR_Reg = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
}

void I2C_Stop(void)
{
	
	TWCR_Reg = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void I2C_SendSlaveAddressWithWrite(u8 slave_address)
{
	
	TWDR_Reg = (slave_address << 1);
	
	
	TWCR_Reg = (1 << TWINT) | (1 << TWEN);
	
	
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
}

void I2C_SendSlaveAddressWithRead(u8 slave_address)
{
	
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

//  Slave Functions 

void I2C_InitSlave(u8 slave_address)
{
	
	TWAR_Reg = (slave_address << 1);
	
	
	TWCR_Reg = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
}

u8 I2C_SlaveListen(void)
{
	while (1)
	{
		
		while (READ_BIT(TWCR_Reg, TWINT) == 0);
		
		u8 status = I2C_GetStatus();
		if (status == I2C_SR_SLA_W_ACK)
		{
			return 1; 
		}
	}
}

u8 I2C_SlaveReceive(void)
{
	
	TWCR_Reg = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	
	
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
	
	return TWDR_Reg;
}

u8 I2C_GetStatus(void)
{
	
	return (TWSR_Reg & 0xF8);
}
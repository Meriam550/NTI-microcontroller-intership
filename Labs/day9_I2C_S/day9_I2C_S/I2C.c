#include "std.h"
#include "bitmath.h"
#include "I2C.h"

void I2C_InitSlave(u8 slave_address)
{
	
	TWAR_Reg = (slave_address << 1);
	
	
	TWCR_Reg = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
}

u8 I2C_SlaveReceiveByte(u8* pData)
{
	
	TWCR_Reg = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	
	
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
	
	u8 status = (TWSR_Reg & 0xF8);
	
	if (status != 0x60 && status != 0x68)
	{
		TWCR_Reg = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		return 0;
	}
	
	
	TWCR_Reg = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	
	
	while (READ_BIT(TWCR_Reg, TWINT) == 0);
	
	status = (TWSR_Reg & 0xF8);
	if (status == 0x80 || status == 0x88)
	{
		
		*pData = TWDR_Reg;
		
		
		TWCR_Reg = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		return 1;
	}
	
	TWCR_Reg = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	return 0;
}

u8 I2C_GetStatus(void)
{
	
	return (TWSR_Reg & 0xF8);
}
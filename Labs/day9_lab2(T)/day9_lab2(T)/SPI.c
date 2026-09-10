#include "SPI.h"
#include "bitmath.h"

/**
 * @brief Initialize SPI as Master with specified mode and prescaler
 * @param mode SPI mode (0-3) combining CPOL and CPHA
 * @param prescaler Clock prescaler for master mode (SPI_PRESCALER_4, 16, 64, 128)
 */
void SPI_InitMaster(u8 mode, u8 prescaler)
{
    // Set data order to MSB first
    CLEAR_BIT(SPCR, DORD);
    
    // Set as Master
    SET_BIT(SPCR, MSTR);
    
    // Set clock polarity and phase based on mode
    if(mode & 0x02)
    {
        SET_BIT(SPCR, CPOL);  // CPOL = 1
    }
    else
    {
        CLEAR_BIT(SPCR, CPOL);  // CPOL = 0
    }
    
    if(mode & 0x01)
    {
        SET_BIT(SPCR, CPHA);  // CPHA = 1
    }
    else
    {
        CLEAR_BIT(SPCR, CPHA);  // CPHA = 0
    }
    
    // Set prescaler (SPR1:SPR0)
    SPCR &= ~(0x03);
    SPCR |= (prescaler & 0x03);
    
    // Disable double speed
    CLEAR_BIT(SPSR, SPI2X);
}

/**
 * @brief Initialize SPI as Slave with specified mode
 * @param mode SPI mode (0-3) combining CPOL and CPHA
 */
void SPI_InitSlave(u8 mode)
{
    // Set data order to MSB first
    CLEAR_BIT(SPCR, DORD);
    
    // Set as Slave
    CLEAR_BIT(SPCR, MSTR);
    
    // Set clock polarity and phase based on mode
    if(mode & 0x02)
    {
        SET_BIT(SPCR, CPOL);  // CPOL = 1
    }
    else
    {
        CLEAR_BIT(SPCR, CPOL);  // CPOL = 0
    }
    
    if(mode & 0x01)
    {
        SET_BIT(SPCR, CPHA);  // CPHA = 1
    }
    else
    {
        CLEAR_BIT(SPCR, CPHA);  // CPHA = 0
    }
}

/**
 * @brief Enable SPI module
 */
void SPI_Enable(void)
{
    SET_BIT(SPCR, SPE);
}

/**
 * @brief Disable SPI module
 */
void SPI_Disable(void)
{
    CLEAR_BIT(SPCR, SPE);
}

/**
 * @brief Transmit and receive data simultaneously (Master mode)
 * @param data Byte to transmit
 * @return Received byte
 */
u8 SPI_Transceive(u8 data)
{
    SPDR = data;
    while(READ_BIT(SPSR, SPIF) == 0);
    return SPDR;
}

/**
 * @brief Send a single byte via SPI (Master mode)
 * @param data Byte to transmit
 */
void SPI_SendByte(u8 data)
{
    SPDR = data;
    while(READ_BIT(SPSR, SPIF) == 0);
}

/**
 * @brief Receive a single byte via SPI (Master mode, generates clock with dummy byte)
 * @return Received byte
 */
u8 SPI_ReceiveByte(void)
{
    SPDR = 0xFF;
    while(READ_BIT(SPSR, SPIF) == 0);
    return SPDR;
}

/**
 * @brief Receive a single byte in Slave mode (waits for Master clock)
 * @return Received byte
 */
u8 SPI_SlaveReceive(void)
{
    while(READ_BIT(SPSR, SPIF) == 0);
    return SPDR;
}
#include "SPI.h"
#include "bitmath.h"


void SPI_InitMaster(u8 mode, u8 prescaler)
{
    // Set data order to MSB first
    CLEAR_BIT(SPCR, DORD);
    
    // Set as Master
    SET_BIT(SPCR, MSTR);
    
    // Set clock polarity and phase based on mode
    // Mode 0: CPOL=0, CPHA=0
    // Mode 1: CPOL=0, CPHA=1
    // Mode 2: CPOL=1, CPHA=0
    // Mode 3: CPOL=1, CPHA=1
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
    SPCR &= ~(0x03);  // Clear SPR1 and SPR0
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
    // Write data to SPI data register
    SPDR = data;
    
    // Wait for transmission complete
    while(READ_BIT(SPSR, SPIF) == 0);
    
    // Return received data
    return SPDR;
}

/**
 * @brief Send a single byte via SPI (Master mode)
 * @param data Byte to transmit
 */
void SPI_SendByte(u8 data)
{
    // Write data to SPI data register
    SPDR = data;
    
    // Wait for transmission complete
    while(READ_BIT(SPSR, SPIF) == 0);
}

/**
 * @brief Receive a single byte via SPI (Master mode, generates clock with dummy byte)
 * @return Received byte
 */
u8 SPI_ReceiveByte(void)
{
    // Send dummy byte to generate clock
    SPDR = 0xFF;
    
    // Wait for transmission complete
    while(READ_BIT(SPSR, SPIF) == 0);
    
    // Return received data
    return SPDR;
}

/**
 * @brief Receive a single byte in Slave mode (waits for Master clock)
 * @return Received byte
 */
u8 SPI_SlaveReceive(void)
{
    // Wait until byte is received from master
    while(READ_BIT(SPSR, SPIF) == 0);
    
    // Return received data
    return SPDR;
}
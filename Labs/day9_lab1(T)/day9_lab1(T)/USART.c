#include "USART.h"
#include "bitmath.h"


void USART_Init(u32 baud_rate)
{
	// 1. Calculate baud rate
	u16 ubrr_value = (u16)((16000000UL / (16UL * baud_rate)) - 1);
	
	// Set baud rate registers
	UBRRH = (u8)(ubrr_value >> 8);
	UBRRL = (u8)ubrr_value;
	
	// 2. Enable TX and RX and Clears the UCSZ2 bit in UCSRB
	SET_BIT(UCSRB, TXEN);
	SET_BIT(UCSRB, RXEN);
	CLEAR_BIT(UCSRB, UCSZ2);
	
	// 3. Configure UCSRC
	u8 temp = 0;
	SET_BIT(temp, URSEL); // Select UCSRC register {0b10000000}
	SET_BIT(temp, UCSZ1); // temp becomes: 0b10000100
	SET_BIT(temp, UCSZ0); //temp becomes: 0b10000110
	
	// Write the complete byte to UCSRC in one single step
	UCSRC = temp;
}


void USART_SendChar(u8 data)
{
    // Wait until transmit buffer is empty
    while(READ_BIT(UCSRA, UDRE) == 0);
    
    // Put data into buffer, sends the data
    UDR = data;
}


u8 USART_Get_Char(void)
{
    // Wait until data is received
    while(READ_BIT(UCSRA, RXC) == 0);
    
    // Return received data
    return UDR;
}
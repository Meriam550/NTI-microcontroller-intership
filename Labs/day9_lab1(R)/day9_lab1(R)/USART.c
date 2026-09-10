#include "USART.h"
#include "bitmath.h"


void USART_Init(u32 baud_rate)
{
    // Calculate baud rate register value
    // UBRR = (F_CPU / (16 * baud_rate)) - 1
    u16 ubrr_value = (u16)((16000000UL / (16UL * baud_rate)) - 1);
    
    // Set baud rate (UBRRH must be written first)
    UBRRH = (u8)(ubrr_value >> 8);
    UBRRL = (u8)ubrr_value;
    
    // Enable transmitter and receiver
    SET_BIT(UCSRB, TXEN);
    SET_BIT(UCSRB, RXEN);
    
    // Set frame format: 8 data bits, 1 stop bit, no parity
    // UCSRC: URSEL=1 (to access UCSRC), UMSEL=0 (async), UPM1:0=00 (no parity)
    // USBS=0 (1 stop bit), UCSZ1:0=11 (8-bit data), UCSZ2=0 (in UCSRB)
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
    CLEAR_BIT(UCSRB, UCSZ2);
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


void USART_SendString(const u8 *str)
{
	// Send each character until null terminator
	while(*str != '\0')
	{
		USART_SendChar(*str);
		str++;
	}
}


void USART_ReceiveString(u8 *str)
{
	u8 index = 0;
	u8 received_char;
	
	// Receive characters until newline or carriage return
	while(1)
	{
		received_char = USART_Get_Char();
		
		// Check for end of line (CR or LF)
		if(received_char == '\r' || received_char == '\n')
		{
			break;
		}
		
		// Store character in buffer
		str[index] = received_char;
		index++;
	}
	
	// Null-terminate the string
	str[index] = '\0';
}
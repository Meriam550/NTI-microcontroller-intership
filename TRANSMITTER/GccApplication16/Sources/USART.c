#include "../Headers/USART.h"
#include "../Headers/Bit_Math.h"


void USART_Init(u32 baud_rate)
{
	// Calculate baud rate register value
	// UBRR = (F_CPU / (16 * baud_rate)) - 1
	u16 ubrr_value = (u16)((8000000UL / (16UL * baud_rate)) - 1);
	// Set baud rate (UBRRH must be written first)
	UBRRH = (u8)(ubrr_value >> 8);
	UBRRL = (u8)ubrr_value;
	// 2. Enable TX and RX and Clears the UCSZ2 bit in UCSRB
	SET_BIT(UCSRB, TXEN);
	SET_BIT(UCSRB, RXEN);
	CLR_BIT(UCSRB, UCSZ2);
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
	while(GET_BIT(UCSRA, UDRE) == 0);
	// Put data into buffer, sends the data
	UDR = data;
}


u8 USART_Get_Char(void)
{
	// Wait until data is received
	while(GET_BIT(UCSRA, RXC) == 0);
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

// Checks if a byte is waiting in the buffer (returns 1 if yes, 0 if empty)
u8 USART_IsDataAvailable(void)
{
	return (GET_BIT(UCSRA, RXC) != 0);
}

// Reads data only if available, without blocking the CPU
u8 USART_Receive_NoBlock(u8 *pData)
{
	if (GET_BIT(UCSRA, RXC) != 0)
	{
		*pData = UDR;
		return 1; // Successfully read a character
	}
	return 0;     // Buffer is empty, did not block
}
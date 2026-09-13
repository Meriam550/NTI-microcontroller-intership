#include "../Headers/DIO.h"
#include "../Headers/Std_types.h"

void DIO_voidSetPinDirection(u8 PortID, u8 PinID, u8 Direction)
{
	if (PortID < 4 && PinID < 8)
	{
		if (Direction == OUTPUT)
		{
			switch (PortID)
			{
				case PORTA: SET_BIT(DDRA, PinID); break;
				case PORTB: SET_BIT(DDRB, PinID); break;
				case PORTC: SET_BIT(DDRC, PinID); break;
				case PORTD: SET_BIT(DDRD, PinID); break;
			}
		}
		else if (Direction == INPUT)
		{
			switch (PortID)
			{
				case PORTA: CLR_BIT(DDRA, PinID); break;
				case PORTB: CLR_BIT(DDRB, PinID); break;
				case PORTC: CLR_BIT(DDRC, PinID); break;
				case PORTD: CLR_BIT(DDRD, PinID); break;
			}
		}
	}
}

void DIO_voidSetPinValue(u8 PortID, u8 PinID, u8 Value)
{
	if (PortID < 4 && PinID < 8)
	{
		if (Value == HIGH)
		{
			switch (PortID)
			{
				case PORTA: SET_BIT(DPORTA, PinID); break;
				case PORTB: SET_BIT(DPORTB, PinID); break;
				case PORTC: SET_BIT(DPORTC, PinID); break;
				case PORTD: SET_BIT(DPORTD, PinID); break;
			}
		}
		else if (Value == LOW)
		{
			switch (PortID)
			{
				case PORTA: CLR_BIT(DPORTA, PinID); break;
				case PORTB: CLR_BIT(DPORTB, PinID); break;
				case PORTC: CLR_BIT(DPORTC, PinID); break;
				case PORTD: CLR_BIT(DPORTD, PinID); break;
			}
		}
	}
}

u8 DIO_u8ReadPinValue(u8 PortID, u8 PinID)
{
	if (PortID < 4 && PinID < 8)
	{
		u8 value = 0;
		switch (PortID)
		{
			case PORTA: value = GET_BIT(PINA, PinID); break;
			case PORTB: value = GET_BIT(PINB, PinID); break;
			case PORTC: value = GET_BIT(PINC, PinID); break;
			case PORTD: value = GET_BIT(PIND, PinID); break;
		}
		return value;
	}
	return 0;
}

void DIO_voidSetPortDirection(u8 PortID, u8 Direction)
{
	if (PortID < 4)
	{
		switch (PortID)
		{
			case PORTA: DDRA = Direction; break;
			case PORTB: DDRB = Direction; break;
			case PORTC: DDRC = Direction; break;
			case PORTD: DDRD = Direction; break;
		}
	}
}

void DIO_voidSetPortValue(u8 PortID, u8 Value)
{
	if (PortID < 4)
	{
		switch (PortID)
		{
			case PORTA: DPORTA = Value; break;
			case PORTB: DPORTB = Value; break;
			case PORTC: DPORTC = Value; break;
			case PORTD: DPORTD = Value; break;
		}
	}
}

u8 DIO_u8ReadPortValue(u8 PortID)
{
	u8 Local_u8Value = 0;
	if (PortID < 4)
	{
		switch (PortID)
		{
			case PORTA: Local_u8Value = PINA; break;
			case PORTB: Local_u8Value = PINB; break;
			case PORTC: Local_u8Value = PINC; break;
			case PORTD: Local_u8Value = PIND; break;
		}
	}
	return Local_u8Value;
}
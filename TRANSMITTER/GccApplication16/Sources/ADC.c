#include "../Headers/ADC.h"
#include "../Headers/DIO.h"

void ADC_init()
{
	ADCSRA_Reg |=(1<<ADEN); //set the enable 
	ADCSRA_Reg |=(1<<ADPS1) | (1<<ADPS0); // prescaler selection -this is a division factor of 8-
	ADMUX_Reg |= (1<<REFS0); //select the voltage reference -this is a AVCC with external capacitor at AREF pin-
}

u16 ADC_Read(u8 channel)
{
	channel &= 0b00000111;  // make sure the channel value doesn't exceed the possible
	ADMUX_Reg &= 0b11111000;// to make sure the previous channel is removed
	ADMUX_Reg |= channel; // choose the channel
	ADCSRA_Reg |=(1<<ADSC); //start conversion
	while(GET_BIT(ADCSRA_Reg, ADIF) != 1); // this gives the ADC time to convert -the ADIF becomes 1 when conversion ends-
	u16 result = ADCL_Reg; //store the lower pins 7-->0
	result |= ((u16)ADCH_Reg<<8);//shifts the bits in the higher ADC and adds them to the lower one -they are originally 1 and 0 then become 9 and 8-
	SET_BIT(ADCSRA_Reg,ADIF);// clear ADIF to be ready for the next read
	return result;
}
/*
 * day9_i2c.c
 *
 * Created: 9/12/2026 1:10:12 AM
 * Author : Meriam
 */ 


#define F_CPU 1000000UL

#include "std.h"
#include "bitmath.h"
#include "DIO_int.h"
#include "ADC.h"
#include "i2c.h"
#include <util/delay.h>

#define SLAVE_ADDRESS    0x01
#define LDR_CHANNEL      0    
#define DARK_THRESHOLD   500   

int main(void)
{
    u16 ldr_val = 0;
    u8 status_byte = 'B';

  
    DIO_voidSetPinDirection(DPORTA, PIN0, INPUT);
    DIO_voidSetPinValue(DPORTA, PIN0, LOW);
	
	
	DIO_voidSetPinDirection(DPORTC, PIN0, INPUT);
	DIO_voidSetPinValue(DPORTC, PIN0, HIGH); //  pull-up on SCL

	DIO_voidSetPinDirection(DPORTC, PIN1, INPUT);
	DIO_voidSetPinValue(DPORTC, PIN1, HIGH); // pull-up on SDA

   
    ADC_Init();
    I2C_InitMaster();

    while (1)
    {
       
        ldr_val = ADC_Read(LDR_CHANNEL);

        
        if (ldr_val < DARK_THRESHOLD)
        {
            status_byte = 'D'; // Dark
        }
        else
        {
            status_byte = 'B'; // Bright
        }

        
        I2C_Start();
        I2C_SendSlaveAddressWithWrite(SLAVE_ADDRESS);
        I2C_WriteData(status_byte);
        I2C_Stop();

        _delay_ms(500);
    }

   
}
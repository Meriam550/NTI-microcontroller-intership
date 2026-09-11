/*
 * day7_lab4.c
 *
 * Created: 9/11/2026 11:55:23 PM
 * Author : Meriam
 */ 



#define F_CPU 1000000UL

#include "std.h"
#include "bitmath.h"
#include "DIO_int.h"
#include "ADC.h"
#include <util/delay.h>

#define LDR_CHANNEL      0         
#define LED_PORT         DPORTC     
#define LED_PIN          PIN0      


#define DARK_THRESHOLD   500        

int main(void)
{
    u16 ldr_val = 0;

    DIO_voidSetPinDirection(DPORTA, PIN0, INPUT);
    DIO_voidSetPinValue(DPORTA, PIN0, LOW); 

   
    DIO_voidSetPinDirection(LED_PORT, LED_PIN, OUTPUT);
    DIO_voidSetPinValue(LED_PORT, LED_PIN, LOW);

   
    ADC_Init();

    while (1)
    {
        
        ldr_val = ADC_Read(LDR_CHANNEL);

        if (ldr_val < DARK_THRESHOLD)
        {
           
            DIO_voidSetPinValue(LED_PORT, LED_PIN, HIGH);
        }
        else
        {
            
            DIO_voidSetPinValue(LED_PORT, LED_PIN, LOW);
        }

        _delay_ms(100);
    }

    return 0;
}
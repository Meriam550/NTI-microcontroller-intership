/*
 * day7_lab2.c
 *
 * Created: 9/11/2026 8:55:14 PM
 * Author : Meriam
 */ 



#define F_CPU 1000000UL

#include "std.h"
#include "DIO_int.h"
#include "ADC.h"
#include "LCD.h"
#include <util/delay.h>



int main(void)
{
    u16 adc_raw = 0;
    u32 voltage_mv = 0;



    DIO_voidSetPinDirection(DPORTA, PIN0, INPUT);
	DIO_voidSetPinValue(DPORTA, PIN0, LOW);

    ADC_Init();
    LCD_init();

    LCD_SendCommand(0x01); // Clear screen
    _delay_ms(2);
    GoToXY(0, 0);
    LCD_SendString((u8*)"  VOLTMETER   ");
    GoToXY(0, 1);
    LCD_SendString((u8*)"Initializing...");
    _delay_ms(1000);

    LCD_SendCommand(0x01); // Clear screen
    _delay_ms(2);

    
    GoToXY(0, 0);
    LCD_SendString((u8*)"Voltage (mV):");

    while (1)
    {
       
        adc_raw = ADC_Read(0);

        
        voltage_mv = ((u32)adc_raw * 5000UL) / 1023UL;

       
        GoToXY(0, 1);
        LCD_SendString((u8*)"Val: ");
       
        LCD_voidWriteNumber((s32)voltage_mv);
        
       
        LCD_SendString((u8*)" mV    ");

       
        _delay_ms(1000);
    }

 
}
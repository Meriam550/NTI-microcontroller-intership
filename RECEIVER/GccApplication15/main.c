#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Headers/Std_types.h"
#include "Headers/Bit_Math.h"
#include "Headers/DIO.h"
#include "Headers/EXTI_interface.h"
#include "Headers/USART.h"
#include "Headers/ADC.h"
#include "Headers/servo_motor.h"

/* Global state variables */
volatile u8  reciever = '0';         // '0': Locked/Armed, '1': Authorized/Disarmed, '2': Alarm
volatile u16 alarm_timer_ms = 0;     // Countdown timer in milliseconds for Buzzer

/* -------------------------------------------------------------
 * Timer0 CTC Mode Initialization for 1 MHz:
 * 1 ms tick at 1 MHz system clock with Prescaler = 8
 * OCR0 = (1,000,000 / (8 * 1000)) - 1 = 124
 * ------------------------------------------------------------- */
void Timer0_CTC_Init(void)
{
    // CTC Mode: WGM01 = 1, WGM00 = 0
    // Prescaler 8: CS02 = 0, CS01 = 1, CS00 = 0
    TCCR0 = (1 << WGM01) | (1 << CS01);
    
    OCR0 = 124;            // 1 ms compare match period
    TCNT0 = 0;             // Clear counter register
    
    TIMSK |= (1 << OCIE0); // Enable Timer0 Compare Match Interrupt
}

/* -------------------------------------------------------------
 * Timer0 Compare Match ISR:
 * Runs every 1 ms. Decrements the countdown timer.
 * Turns OFF Buzzer when countdown reaches 0.
 * ------------------------------------------------------------- */
ISR(TIMER0_COMP_vect)
{
    if (alarm_timer_ms > 0)
    {
        alarm_timer_ms--;
        DIO_voidSetPinValue(PORTC, PIN0, HIGH); // Keep Buzzer ON (steady 5V)
    }
    else
    {
        // 5 seconds elapsed -> Turn OFF Buzzer completely
        DIO_voidSetPinValue(PORTC, PIN0, LOW);
    }
}

/* -------------------------------------------------------------
 * EXTI0 (INT0) Callback:
 * Triggered when the door sensor detects the door opening.
 * ------------------------------------------------------------- */
void SecurityAlarm_ON(void)
{
    // If the system is NOT disarmed ('1'), sound the alarm
    if (reciever != '1')
    {
        DIO_voidSetPinValue(PORTC, PIN0, HIGH); // Turn ON Buzzer immediately
        alarm_timer_ms = 500;                  // Keep Buzzer active for 5000 ms (5 seconds)
    }
}

int main(void)
{
    /* 1. Pin Configurations */
    // Alert / Buzzer: PORTC PIN0 as OUTPUT
    DIO_voidSetPinDirection(PORTC, PIN0, OUTPUT);
    DIO_voidSetPinValue(PORTC, PIN0, LOW);        // Buzzer initially OFF
    
    // Door Sensor: PORTD PIN2 (EXTI0 / INT0) as INPUT
    DIO_voidSetPinDirection(PORTD, PIN2, INPUT);
    DIO_voidSetPinValue(PORTD, PIN2, HIGH);       // Enable internal pull-up if needed
    
    // Optional peripherals (LDRs, Servo, Lamp)
    DIO_voidSetPinDirection(PORTA, PIN0, INPUT);  // LDR Lighting
    DIO_voidSetPinDirection(PORTA, PIN1, INPUT);  // LDR Curtains
    DIO_voidSetPinDirection(PORTB, PIN0, OUTPUT); // Room Lamp
    SET_BIT(DDRD, 5);                             // PD5: Servo motor (OC1A)
    
    /* 2. Peripherals Initialization */
    USART_Init(9600);
    Timer0_CTC_Init();
    ADC_init();
    ServoMotor_Init();
    
    /* 3. Configure EXTI INT0 (Door Sensor) */
    MEXTI_voidSetCallBackInt0(&SecurityAlarm_ON);
    MEXTI_voidInitInt0();                          // Configured for Rising/Falling edge
    MEXTI_voidEnableInt0();
    MEXTI_voidEnableGlobalInterrupt();             // Enable global interrupts (sei)
    
    u8 new_cmd = 0;
    
    while (1)
    {
        // Check non-blocking UART command from Transmitter MCU
        if (USART_Receive_NoBlock(&new_cmd))
        {
            reciever = new_cmd;
            
            if (new_cmd == '1')
            {
                // Correct password -> Silence buzzer & authorize entry
                DIO_voidSetPinValue(PORTC, PIN0, LOW);
                alarm_timer_ms = 0;
            }
            else if (new_cmd == '2')
            {
                // 3 Wrong password attempts -> Trigger buzzer for 5 seconds
                DIO_voidSetPinValue(PORTC, PIN0, HIGH);
                alarm_timer_ms = 500;
            }
        }
        
        // If authorized ('1'), execute smart room functions
        if (reciever == '1')
        {
            // Automatic Lighting Control
            u16 ldr_light = ADC_Read(0);
            if (ldr_light >= 350)
            {
                DIO_voidSetPinValue(PORTB, PIN0, LOW);
            }
            else
            {
                DIO_voidSetPinValue(PORTB, PIN0, HIGH);
            }
            
            // Automatic Curtain Control
            u16 ldr_curtain = ADC_Read(1);
            if (ldr_curtain > 400)
            {
                ServoMotor_OCA1_Angle(180);
            }
            else
            {
                ServoMotor_OCA1_Angle(0);
            }
        }
    }
}
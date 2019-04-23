/*
 * WDT1.c
 *
 * Created: 4/23/2019 9:03:04 PM
 * Author : Eng. Hossam
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>.
#include <util/delay.h>
#include <stdlib.h>
#include "LCD.h"

volatile uint16_t i=0;
void wdt_init()
{
	cli();
	wdt_reset();
	MCUSR &= ~(1<<WDRF);
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	WDTCSR =  (1<<WDP1) | (1<<WDP2) | (1<<WDIE);
	sei();
}
int main(void)
{
	DDRB |= (1<<DDB5);
	char String[10];
	wdt_init();
	LCD_Init();
	LCD_String_xy(0,0,"WDT");
    while (1) 
    {
		utoa(i,String,10);
		LCD_String_xy(1,0,String);
    }
}

ISR(WDT_vect) //Watchdog timeout ISR
{
	i++;
	PORTB ^= (1<<PORTB5);
}

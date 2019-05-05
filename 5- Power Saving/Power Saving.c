/*
 * test_Power_Saving.c
 *
 * Created: 5/3/2019 10:11:04 PM
 * Author : Eng. Hossam
 */ 
#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/power.h>


int main(void)
{
	clock_prescale_set(clock_div_8);
    DDRB |= (1<<DDB5);
	PRR |= 0xFF;
	//set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	//sleep_enable();
	
    while (1) 
    {
		PORTB ^= (1<<PORTB5);
		_delay_ms(500);
    }
}


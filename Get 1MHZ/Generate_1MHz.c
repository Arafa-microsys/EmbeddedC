/*
 * Generate_1MHz.c
 *
 * Created: 4/30/2019 10:24:36 PM
 * Author : Eng. Hossam
 */ 

/*
Timer 0
output    OC0A   (PD6)
output    OC0B   (PD5)

Timer 1
output    OC1A   (PB1)
output    OC1B   (PB2)

Timer 2
output    OC2A   (PB3)
output    OC2B   (PD3)
*/
#include <avr/io.h>

void init_timer()
{
	TCCR0A = 0;
	TCCR0B = 0;
	TCNT0  = 0;
	OCR0A = 7;   // toggle after counting to 8 --- 1 Tick (62.5x10^-9) -> 8 Ticks = 500us -> to obtain 500Khz -> 16 Ticks
	TCCR0A |= (1 << COM0A0);   // Toggle OC1A on Compare Match OC
	TCCR0A |= (1 << WGM01);    // CTC mode
	TCCR0B |= (1 << CS00);     // clock on, no pre-scaler
}
int main(void)
{
	DDRD |= (1<<DDD6);
	init_timer();
    /* Replace with your application code */
    while (1) 
    {
    }
}


/*
 * Timer.c
 *
 * Created: 3/31/2019 8:59:41 PM
 * Author : Eng. Hossam
 */ 
//255-(16MHZ/Prescaler/Disierd Freq)=		255-(16MHZ/1024/1)=15625		255-((16MHz/1024/100)*10^6)=99  100hz->10ms
//Freq=1/Time = 1 HZ
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRD |= (1<<DDD4);
	OCR0A = 99;
	TCCR0A |= (1<<WGM01) ;
	TCCR0B |= (1<<CS00) | (1<<CS02);// Prescaler = 1024
	TCNT0=0;
	TIMSK0 |= (1<<OCIE0A);
	sei();
    /* Replace with your application code */
    while (1) 
    {
    }
}

ISR(TIMER0_COMPA_vect)
{
	PORTD ^= (1<<PORTD4);
}


/*
 * Millis().c
 *
 * Created: 4/3/2019 12:51:31 AM
 * Author : Eng. Hossam
 */ 

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
volatile unsigned long millis_value;
unsigned long time1=0;
unsigned long millis();
int main(void)
{
	DDRB |= (1<<DDB5);
	OCR0A = 249;
	TCCR0A |= (1<<WGM01) ;
	TCCR0B |= (1<<CS00) | (1<<CS01);// Prescaler = 64
	TIMSK0 |= (1<<OCIE0A);
	sei();
	time1=millis();
    /* Replace with your application code */
    while (1) 
    {
		if((unsigned long)millis()-time1>1000)
		{
			PORTB ^= (1<<PORTB5);
			time1=millis();
		}
	}
}

ISR(TIMER0_COMPA_vect)
{
	millis_value++; 
}

unsigned long millis()
{
	unsigned long m;

	// Disable interrupts while we read millis_value or we might get an
	// inconsistent value (e.g. in the middle of a write to millis_value)
	cli();
	m = millis_value;
	sei();
	return m;
}




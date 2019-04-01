#include <avr/io.h>
#include <avr/interrupt.h>    // Needed to use interrupts
int main(void)
{
	DDRB &= ~(1 << DDB0) | (1 << DDB1) | (1 << DDB2);         // Clear the PB0 pin
	DDRB |= (1<<DDB3) | (1<<DDB4) | (1<<DDB5);
	// PB0 (PCINT0 pin) is now an input

	PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2);        // turn On the Pull-up
	// PB0 is now an input with pull-up enabled

	PCICR |= (1 << PCIE0);     // set PCIE0 to enable PCMSK0 scan
	PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2);   // set PCINT0 to trigger an interrupt

	sei();                     // turn on interrupts

	while(1)
	{
		
	}
}



ISR (PCINT0_vect)
{
	
	if((PINB & (1<<PINB0))==0)
	{
		PORTB ^= (1<<PORTB3);
	}else 
	
	if(PINB & (1<<PINB1)==0)
	{
		PORTB ^= (1<<PORTB4);
	}

	if(PINB & (1<<PINB2)==0)
	{
		PORTB ^= (1<<PORTB5);
	}
	
}

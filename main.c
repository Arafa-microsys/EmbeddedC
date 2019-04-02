/*
 * PhaseCorrectPWM.c
 *
 * Created: 4/2/2019 7:47:45 PM
 * Author : Eng. Hossam
 */ 

#include <avr/io.h>


int main(void)
{
	DDRD |= (1 << DDD5) | (1<<DDD6);
	// as output
	OCR0A = 180;
	OCR0B = 50;
	// set PWM for 50% duty cycle at 10bit
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
	// set non-inverting mode
	TCCR0A |= (1 << WGM00);
	// set 10bit phase corrected PWM Mode
	TCCR0B |= (1 << CS02); //Prescaler = 256
	// set prescaler to 8 and starts PWM
	while (1)
	{
	}
}


/*
 * Fast_PWM.c
 *
 * Created: 4/1/2019 10:07:05 PM
 * Author : Eng. Hossam
 */ 

#include <avr/io.h>


int main(void)
{
	DDRD |= (1 << DDD5);
	DDRD |= (1 << DDD6);
	// PD6 is now an output
	// PD5 is now an output
    /* Replace with your application code */
	TCCR0A |= (1<<COM0A1) | (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);
	TCCR0B |= (1<<CS02);//Prescaler = 256	Freq=(16MHz/(256*256))
	OCR0A = 180;//PD6
	OCR0B = 50;//PD5
    while (1) 
    {
    }
}


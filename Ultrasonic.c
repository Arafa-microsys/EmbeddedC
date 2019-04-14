/*
 * Ultrasonic.c
 *
 * Created: 4/9/2019 7:05:55 PM
 * Author : Eng. Hossam
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include "LCD.h"
volatile uint16_t capt1,capt2;
volatile uint8_t mask=0;
volatile uint16_t ov;
volatile uint16_t ovf;
int main(void)
{
    unsigned long count;
	double distance;
	char string[10];
	LCD_Init();
	LCD_String_xy(0,0,"Ultrasonic Sens");
	DDRB |= (1<<DDB1);
	DDRB &= ~(1<<DDB0);
	cli();
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	TCCR1B |= (1<<ICES1) | (1<<CS10);//Rising Edge, Prescaler=1
	TIMSK1 |= (1<<ICIE1) | (1<<TOIE1);
	sei();
	
    while (1) 
    {
		PORTB |= (1<<PORTB1);
		_delay_us(10);
		PORTB &= ~(1<<PORTB1);
		if(mask==2)
		{
			mask=0;
			count = ((unsigned long)capt2+(unsigned long)(ovf*65536))-(unsigned long)capt1;
			distance = (double)count/932.95;
			dtostrf(distance,2,2,string);
			strcat(string,"cm  ");
			LCD_String_xy(1,0,"Dist= ");
			LCD_String_xy(1,7,string);
			_delay_ms(350);
			ovf=0;ov=0;
			TCCR1B |= (1<<ICES1);
			TIFR1=(1<<ICF1) | (1<<TOIE1);
			TIMSK1 |= (1<<ICIE1) | (1<<TOIE1);
		}
    }
}

ISR(TIMER1_OVF_vect)
{
	ov++;
}

ISR(TIMER1_CAPT_vect)
{
	if(mask==0)
	{
		capt1=ICR1;
		TCCR1B &= ~(1<<ICES1);//Falling Edge
		ov=0;
	}else if(mask==1)
	{
		capt2=ICR1;
		ovf=ov;
		TIMSK1 &= ~ ((1<<ICIE1)|(1<<TOIE1));//Disable Input Capture Interrupt, TOV
	}
	mask++;
}
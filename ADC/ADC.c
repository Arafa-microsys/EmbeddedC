/*
 * ADC.c
 *
 * Created: 6/20/2019 9:52:47 PM
 * 
 */ 
#define F_CPU 16000000UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#define VREF 5
#define POT 10000

void InitADC()
{
	// Select Vref=AVcc
	ADMUX |= (1<<REFS0);
	//set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}
uint16_t ReadADC(uint8_t ADCchannel)
{
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADC;
}
int main()
{
	double vbg, potval;
	char str1[16];
	char str2[16];
	//initialize ADC
	InitADC();
	LCD_Init ();
	while(1)
	{
		potval=(double)POT/1023*ReadADC(0);
		dtostrf(potval, 5, 1, str1);
		LCD_String_xy (0,0, str1);
		vbg=(double)VREF/1023*ReadADC(0);
		dtostrf(vbg, 5, 2, str2);
		LCD_String_xy (1, 0, str2);
		_delay_ms(1000);
	}
}

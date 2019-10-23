/*
 * SPI.c
 *
 * Created: 10/23/2019 6:28:41 PM
 * Author : Eng. Hossam
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>	
#include <util/delay.h>	
#include <stdio.h>	
#include <string.h>	
#include "LCD.h"
#define MOSI DDB3
#define MISO DDB4
#define SCK DDB5
#define SS DDB2
#define SS_Enable PORTB &= ~(1<<PORTB2)
#define SS_Disable PORTB |= (1<<PORTB2)
void SPI_Init()		// SPI Initialize function
{
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);	// Make MOSI, SCK, SS as Output pin 
	DDRB &= ~(1<<MISO);			// Make MISO pin as input pin 
	//PORTB |= (1<<PORTB2);			// Make high on SS pin
	SS_Disable;
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	// Enable SPI in master mode with Fosc/16
	//SPSR &= ~(1<<SPI2X);		// Disable speed doubler
}

void SPI_Write(char data)		//SPI write data function
{
	//char flush_buffer;
	SPDR = data;			// Write data to SPI data register
	while(!(SPSR & (1<<SPIF)));	// Wait till transmission complete 
	//flush_buffer = SPDR;		// Flush received data 
	
}



int main(void)
{
	uint8_t count;
	char buffer[10];
	LCD_Init();
	SPI_Init();
	LCD_String_xy(0, 0, "Master Device");
	LCD_String_xy(1, 0, "Sending Data:    ");
	SS_Enable;
	count = 0;
    while (1) 
    {
		SPI_Write(count);
		sprintf(buffer, "%d   ", count);
		LCD_String_xy(1, 13, buffer);
		count++;
		_delay_ms(500);
    }
}


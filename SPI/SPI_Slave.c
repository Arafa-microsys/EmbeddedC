/*
 * SPI_Slave.c
 *
 * Created: 10/23/2019 6:59:43 PM
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
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));  // Make MOSI, SCK, SS as input pins
	DDRB |= (1<<MISO);			// Make MISO pin as output pin
	SPCR = (1<<SPE);			//Enable SPI in slave mode
}

char SPI_Receive()			/* SPI Receive data function */
{
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}

int main(void)
{
    uint8_t count;
    char buffer[10];
    
    LCD_Init();
    SPI_Init();
    
    LCD_String_xy(0, 0, "Slave Device");
    LCD_String_xy(1, 0, "Receive Data:    ");
    while (1)			/* Receive count continuous */
    {
	    count = SPI_Receive();
	    sprintf(buffer, "%d   ", count);
	    LCD_String_xy(1, 13, buffer);
    }
}


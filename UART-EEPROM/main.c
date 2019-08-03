/*
 * UART.c
 *
 * Created: 7/19/2019 4:49:51 PM
 * Author : Eng. Hossam
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
char Rarray[20];
void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C |=  (1 << UCSZ00) | (1 << UCSZ01);
}
void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while (! (UCSR0A & (1<<UDRE0)));  /* Wait for empty transmit buffer */
	UDR0 = data ;
}
unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}
//ABCDEF
void USART_SendString(char *str)
{
	unsigned char i=0;
	while(str[i]!=0)
	{
		USART_Transmit(str[i]);
		i++;
	}
}

void Read_EEPROM()
{
	eeprom_read_block(Rarray,(void*)100,21);
	for(int i=0;i<20;i++)
	{
		if(Rarray[i]!=0)
		{
			USART_Transmit(Rarray[i]);
		}
	}
	
	
}
int main(void)
{
	USART_Init(MYUBRR);
	char m;
	char r[20];
	uint8_t i=0;
	Read_EEPROM();
    while (1) 
    {
		/*
		m=USART_Receive();
		USART_Transmit(m);
		USART_Transmit('\r');
		//_delay_ms(500);
		USART_SendString("Hello World! \r");
		USART_SendString("Test 12345 \r");
		_delay_ms(500);
		*/
		//Hossam
		m=USART_Receive();
		if(m!='\r')
		{
			r[i]=m;
			i++;
		}else if(m=='\r')
		{
			eeprom_write_block(r,(void*)100,20);	// Write Warray from EEPROM address 100
			USART_SendString(r);
			for(int j=0;j<20;j++)
			{
				r[j]=0;
			}
			i=0;
		}
		
    }
}




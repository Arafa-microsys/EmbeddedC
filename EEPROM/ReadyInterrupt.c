/*
 * CFile1.c
 *
 * Created: 5/14/2019 1:25:23 AM
 *  Author: Eng. Hossam
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
//EEPROM address initial 0
volatile uint16_t eepromaddress;
//string array index initial 0
volatile uint8_t i;
//message to be written to EEPROM
uint8_t message[] ="Write to EEPROM";
//EEPROM writing ISR
ISR(EE_READY_vect)
{
	/*check if not end of string and address
	didn't reach end of EEPROM*/
	if ((message[i])&&(eepromaddress<=E2END))
	{
		//loads address and increments for next load
		EEAR=eepromaddress++;
		//loads current byte and increments index for next load
		EEDR=message[i++];
		//master write enable
		EECR|=(1<<EEMPE);
		//strobe eeprom write
		EECR|=(1<<EEPE);
	}
	else
	{
		//disable eeprom ready interrupt
		EECR &= ~(1<<EERIE);
	}
}
int main(void)
{
	//Enable eeprom ready interrupt
	EECR |= (1<<EERIE);
	//enable global interrupts
	sei();
	while(1)
	{
		//do other tasks or sleep
	}
}
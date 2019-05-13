/*
 * EEPROM1.c
 *
 * Created: 5/11/2019 11:11:15 PM
 * Author : Eng. Hossam
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCD.h"

#define EEADDR 10
#define EEDATA 200
int main(void)
{
	char String[10];
	uint8_t EEByte;	
	DDRB |= (1<<DDB5);
	LCD_Init();
	LCD_String_xy(0,0,"Value");
	//eeprom_write_byte ((uint8_t*)EEADDR, EEDATA);
	EEByte = eeprom_read_byte((uint8_t*)EEADDR);
	utoa(EEByte,String,10);
	LCD_String_xy(1,0,String);
	while(1)
	{
		
	}
}
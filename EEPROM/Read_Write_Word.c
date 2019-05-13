/*
 * EEPROM_WORD.c
 *
 * Created: 5/13/2019 12:59:17 AM
 * Author : Eng. Hossam
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCD.h"
//Address 1023
#define EEADDR 20
//Data which will be stored
#define EEDATA 65535
uint16_t EEByte;
int main(void)
{
	char String[10];
	//put EEPROM data to this variable
	
	DDRB |= (1<<DDB5);
	LCD_Init();
	LCD_String_xy(0,0,"Value");
	//eeprom_write_word ((uint16_t*)EEADDR, EEDATA);
	EEByte = eeprom_read_word((uint16_t*)EEADDR);
	utoa(EEByte,String,10);
	LCD_String_xy(1,0,String);
	while(1)
	{
	}
}
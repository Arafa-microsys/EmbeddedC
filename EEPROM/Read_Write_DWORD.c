/*
 * EEPROM_DWORD.c
 *
 * Created: 5/13/2019 1:05:42 AM
 * Author : Eng. Hossam
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCD.h"
//Address 1023
#define EEADDR 0x01
//Data which will be stored
#define EEDATA 4294967295
uint32_t EEByte;
int main(void)
{
	char String[10];	
	DDRB |= (1<<DDB5);
	LCD_Init();
	LCD_String_xy(0,0,"Value");
	//eeprom_write_dword ((uint32_t*)EEADDR, EEDATA);
	EEByte = eeprom_read_dword((uint32_t*)EEADDR);
	ultoa(EEByte,String,10);
	LCD_String_xy(1,0,String);
	while(1)
	{
	}
}
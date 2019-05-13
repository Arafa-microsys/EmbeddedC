/*
 * EEPROM_Block.c
 *
 * Created: 5/13/2019 1:17:52 AM
 * Author : Eng. Hossam
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "LCD.h"
int main(void)
{
	char Rarray[15],Warray[] = "ABCDEFGHIJKLMNO ";	
	DDRB |= (1<<DDB5);
	LCD_Init();
	//eeprom_write_block(Warray,(void*)100,16);	// Write Warray from EEPROM address 0
	LCD_String_xy(0,0,"Array Value");
	
	eeprom_read_block(Rarray,(void*)100,16);
	LCD_String_xy(1,0,Rarray);
	while(1)
	{
		
	}
}
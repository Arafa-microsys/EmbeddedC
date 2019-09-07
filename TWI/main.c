/*
 * TWI.c
 *
 * Created: 8/31/2019 9:53:36 PM
 * Author : Eng. Hossam
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include <string.h>
#define EEPROM_Write_Addess		0xA0 //10100000
#define EEPROM_Read_Addess		0xA1 //10100001
void TWIInit()
{
	//set SCL to 400kHz
	TWSR = 0x00;
	TWBR = 0x0C;
	//enable TWI
	TWCR = (1<<TWEN);
}
void TWIStart()						/* I2C start function */
{
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Enable TWI, generate start condition and clear interrupt flag */
	while ((TWCR & (1<<TWINT)) == 0);							/* Wait until TWI finish its current job (start condition) */	
}

void TWIStop()												/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);					/* Enable TWI, generate stop condition and clear interrupt flag */
	while(TWCR & (1<<TWSTO));								/* Wait until stop condition execution */
}


void TWIWrite(char data)								/* I2C write function */
{
	TWDR = data;											/* Copy data in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while ((TWCR & (1<<TWINT)) == 0);							/* Wait until TWI finish its current job (Write operation) */
}

char TWIReadACK()											/* I2C read ack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);					/* Enable TWI, generation of ack and clear interrupt flag */
	while ((TWCR & (1<<TWINT)) == 0);							/* Wait until TWI finish its current job (read operation) */
	return TWDR;											/* Return received data */
}

char TWIReadNACK()										/* I2C read nack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);								/* Enable TWI and clear interrupt flag */
	while ((TWCR & (1<<TWINT)) == 0);						/* Wait until TWI finish its current job (read operation) */
	return TWDR;											/* Return received data */
}

EEPROM_Read(char Address,char* ptr)
{
	TWIStart();/* Start I2C with device write address */
	TWIWrite(EEPROM_Write_Addess);
	TWIWrite(Address);		/* Write start memory address */
	TWIStart();/* Repeat start I2C SLA+R */
	TWIWrite(EEPROM_Read_Addess);
	for (int i = 0; i<strlen(ptr); i++)/* Read data with acknowledgment */
	{
		LCD_Char(TWIReadACK());
	}
	
	TWIStop();			/* Stop I2C */
}
EEPROM_Write(char Address,char *ptr)// Hossam -> 0x00  H->0x00 o->0x01 s->0x02 ----
{
	TWIStart();		/* Start I2C*/
	TWIWrite(EEPROM_Write_Addess);
	TWIWrite(Address);		/* Write start memory address for data write */
	for (int i = 0; i<strlen(ptr); i++)/* Write array data */
	{
		TWIWrite(ptr[i]);
	}
	TWIStop();			/* Stop I2C */
	_delay_ms(10);
}
int main(void)
{
	char array[] = "Ahmed1";	/* Declare array to be print */
	char arrayR[]="     ";
	LCD_Init();			/* Initialize LCD */
	TWIInit();			/* Initialize I2C */
	LCD_String_xy(0,0,"EEPROM Read:");
	LCD_String_xy(1,0,"");
	EEPROM_Write(0x7E0,array); //Loc->2016
	//EEPROM_Read(0x00,array);
	
}
	 


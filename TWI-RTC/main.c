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
#include <stdio.h>
#define ReadMode   0xD1  // DS1307 ID
#define WriteMode  0xD0  // DS1307 ID
#define SecondRegAddress   0x00   // Address to access Ds1307 SEC register
#define DateRegAddress     0x04   // Address to access Ds1307 DATE register
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


typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}rtc_t;

//rtc_t rtc;
//rtc.sec=0x10;
//rtc.min=0x50;

void RTC_SetDateTime(rtc_t *rtc)
{
	TWIStart();                          // Start I2C communication
	TWIWrite(WriteMode);      // connect to DS1307 by sending its ID on I2c Bus
	TWIWrite(SecondRegAddress); // Request sec RAM address at 00H
	TWIWrite(rtc->sec);                    // Write sec from RAM address 00H//
	TWIWrite(rtc->min);                    // Write min from RAM address 01H
	TWIWrite(rtc->hour);                    // Write hour from RAM address 02H
	TWIWrite(rtc->weekDay);                // Write weekDay on RAM address 03H
	TWIWrite(rtc->date);                    // Write date on RAM address 04H
	TWIWrite(rtc->month);                    // Write month on RAM address 05H
	TWIWrite(rtc->year);                    // Write year on RAM address 06h
	TWIStop();                              // Stop I2C communication after Setting the Date
}

void RTC_GetDateTime(rtc_t *rtc)
{
	
	TWIStart();                            // Start I2C communication
	TWIWrite(WriteMode);        // connect to DS1307 by sending its ID on I2c Bus
	TWIWrite(SecondRegAddress); // Request Sec RAM address at 00H
	//TWIStop();                                // Stop I2C communication after selecting Sec Register
	
	TWIStart();                            // Start I2C communication
	TWIWrite(ReadMode);            // connect to DS1307(Read mode) by sending its ID
	rtc->sec = TWIReadACK();                
	rtc->min = TWIReadACK();                 
	rtc->hour= TWIReadACK();               
	rtc->weekDay = TWIReadACK();           
	rtc->date= TWIReadACK();             
	rtc->month=TWIReadACK();            
	rtc->year =TWIReadACK();            
	TWIStop();                              // Stop I2C communication after reading the Date
}

int main(void)
{
	LCD_Init();			/* Initialize LCD */
	TWIInit();			/* Initialize I2C */
	rtc_t rtc;
	rtc.hour = 0x10; //  10:40:20 am
	rtc.min =  0x40;
	rtc.sec =  0x00;
	rtc.date = 0x01; //1st Jan 2016
	rtc.month = 0x01;
	rtc.year = 0x16;
	rtc.weekDay = 6; //Sunday as first day=1.
	RTC_SetDateTime(&rtc);  //  10:40:20 am, 1st Jan 2016
	char buffer[20];
	char* days[7]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	while(1)
	{
		 RTC_GetDateTime(&rtc);
		 sprintf(buffer, "%02x:%02x:%02x  ", rtc.hour, rtc.min, rtc.sec);
		 LCD_String_xy(0,0,buffer);
		 sprintf(buffer, "%02x/%02x/%02x %3s ", rtc.date, rtc.month, rtc.year,days[rtc.weekDay-1]);
		 LCD_String_xy(1,0,buffer);
		 
	}
}
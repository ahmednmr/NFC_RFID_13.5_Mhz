/*
 * lcd_prog.c
 *
 *  Created on: Jan 20, 2019
 *      LCD_ControlPORTuthor: Nmr
 */


#include "LCD.h"


void LCD_VidInit(void)
{
	LCD_DDR_DATA |= 0xf0;
	LCD_DDR_Control |=(1<<LCD_ENABLE_PIN)|(1<<LCD_RS_PIN);


	LCD_PORT_DATA &=~(0xf0);
	LCD_PORT_Control &=~((1<<LCD_ENABLE_PIN)|(1<<LCD_RS_PIN));

	_delay_ms(2);

	LCD_vidSendCommand(0x33);
	LCD_vidSendCommand(0x32);
	LCD_vidSendCommand(0x28);    /* initalization commands*/

	LCD_vidSendCommand(0x0e);
	LCD_vidSendCommand(0x01);
	_delay_ms(2);

	LCD_vidSendCommand(0x06);

}

void LCD_vidSendCommand(unsigned char command)
{


	LCD_PORT_Control &=~(1<<LCD_RS_PIN);   //RS zero send command


	LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F) | (command & 0xF0); /* sending upper nibble */

	LCD_PORT_Control |=(1<<LCD_ENABLE_PIN);         /* Enable pulse */
	_delay_ms(2);
	LCD_PORT_Control &=~(1<<LCD_ENABLE_PIN);

	_delay_us(1);

	LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F) | (command << 4);  /* sending lower nibble */
	LCD_PORT_Control |=(1<<LCD_ENABLE_PIN);         /* Enable pulse */
	_delay_ms(2);
	LCD_PORT_Control &=~(1<<LCD_ENABLE_PIN);

	_delay_ms(2);


}


void LCD_vidsendData(unsigned char character)
{

	LCD_PORT_Control |=(1<<LCD_RS_PIN);    //RS 1 send Data

	LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F) | (character & 0xF0); /* sending upper nibble */

	LCD_PORT_Control |=(1<<LCD_ENABLE_PIN);         /* Enable pulse */
	_delay_ms(2);
	LCD_PORT_Control &=~(1<<LCD_ENABLE_PIN);

	_delay_us(1);

	LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F) | (character << 4);  /* sending lower nibble */
	LCD_PORT_Control |=(1<<LCD_ENABLE_PIN);         /* Enable pulse */
	_delay_ms(2);
	LCD_PORT_Control &=~(1<<LCD_ENABLE_PIN);

	_delay_ms(2);


}

void LCD_vidsendword(char * word)
{
	while(*word!='\0')
	{
		LCD_vidsendData(*word);
		word++;

	}


}


void LCD_vidsend_sentance(char * word)
{
	U8 i=0;
	LCD_vidClear();
	while(*word!='\0')
	{
		LCD_vidsendData(*word);
		word++;
		i++;
		if(i==16)
		{
			LCD_vidGoTo(1,0)	;
		}

	}


}


void LCD_vidClear(void)
{
	LCD_vidSendCommand(0x01);
}


void LCD_vid_Save_in_CGRAM(void)
{
	LCD_vidSendCommand(0b01000000);  //0x40   0b 0100 0000

	//   save Person
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b00100);
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b10101);
	LCD_vidsendData(0b00100);
	LCD_vidsendData(0b01010);
	LCD_vidsendData(0b01010);

	//   save smile
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b01010);
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b10001);
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b00000);

	//   save LOCK
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b10001);
	LCD_vidsendData(0b10001);
	LCD_vidsendData(0b11111);
	LCD_vidsendData(0b11011);
	LCD_vidsendData(0b11011);
	LCD_vidsendData(0b11111);
	LCD_vidsendData(0b00000);


	//   save Heart
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b01010);
	LCD_vidsendData(0b10101);
	LCD_vidsendData(0b10001);
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b00100);
	LCD_vidsendData(0b00000);


	///  SAVE ?
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00001);
	LCD_vidsendData(0B00001);
	LCD_vidsendData(0B00001);
	LCD_vidsendData(0B11111);
	LCD_vidsendData(0B00000);

	///  SAVE ?
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B01110);
	LCD_vidsendData(0B10001);
	LCD_vidsendData(0B01110);

	///  SAVE  ?
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B01110);
	LCD_vidsendData(0B00001);
	LCD_vidsendData(0B11111);
	LCD_vidsendData(0B00000);


	///  SAVE ?
	LCD_vidsendData(0b00110);
	LCD_vidsendData(0B00100);
	LCD_vidsendData(0B01110);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00100);
	LCD_vidsendData(0B00100);
	LCD_vidsendData(0B00100);
	LCD_vidsendData(0B00100);






}


void LCD_vidGoTo(unsigned char col,unsigned char Row)
{
	if(col==0)
	{
		LCD_vidSendCommand(0b10000000|Row);
	}

	else if(col==1)
	{
		LCD_vidSendCommand(0b11000000|Row);

	}


}



void LCD_SEND_number(int number)
{
	char buffer[20];

	itoa(number,buffer,10);
	LCD_vidsendword(buffer);


}


void  LCD_SEND_long_number(unsigned long number)
{
   char buffer[20];

   ultoa(number,buffer,10);
   LCD_vidsendword(buffer);


}



void LCD_SEND_number_binary(int number)
{
	char c=0,k=0;

	for (c = 8; c > 0; c--)
	{
		k = number >> (c-1);

		if (k & 1)
			LCD_vidsendData('1');
		else
			LCD_vidsendData('0');

	}


}


void LCD_SEND_number_hex(unsigned char number)
{
	unsigned char high_nipple=number&0xF0;
	high_nipple>>=4;
	unsigned char low_nipple=number&0x0F;

	//    LCD_vidsendword("0x");
	if(high_nipple<10)
	{
		LCD_SEND_number(high_nipple);
	}
	else if(high_nipple==10)
	{

		LCD_vidsendData('A');
	}

	else if(high_nipple==11)
	{

		LCD_vidsendData('B');
	}

	else if(high_nipple==12)
	{

		LCD_vidsendData('C');
	}

	else if(high_nipple==13)
	{

		LCD_vidsendData('D');
	}

	else if(high_nipple==14)
	{

		LCD_vidsendData('E');
	}

	else if(high_nipple==15)
	{

		LCD_vidsendData('F');
	}


	if(low_nipple<10)
	{
		LCD_SEND_number(low_nipple);
	}
	else if(low_nipple==10)
	{

		LCD_vidsendData('A');
	}

	else if(low_nipple==11)
	{

		LCD_vidsendData('B');
	}

	else if(low_nipple==12)
	{

		LCD_vidsendData('C');
	}

	else if(low_nipple==13)
	{

		LCD_vidsendData('D');
	}

	else if(low_nipple==14)
	{

		LCD_vidsendData('E');
	}

	else if(low_nipple==15)
	{

		LCD_vidsendData('F');
	}


}

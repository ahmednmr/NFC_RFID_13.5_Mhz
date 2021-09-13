/*
 * LCD_interface.h
 *
 *  Created on: Jan 20, 2019
 *      Author: Nmr
 */

#ifndef LCD_H_
#define LCD_H_

#include<avr/delay.h>
#include<avr/io.h>
#include<stdlib.h>


#define LCD_DDR_DATA      DDRB
#define LCD_PORT_DATA     PORTB
#define LCD_DDR_Control   DDRC
#define LCD_PORT_Control  PORTC
#define LCD_ENABLE_PIN    PD7
#define LCD_RS_PIN        PD6


void LCD_VidInit(void);
void LCD_vidSendCommand(unsigned char command);
void LCD_vidsendData(unsigned char character);
void LCD_vidsendword(char * word);
void LCD_vidClear(void);
void LCD_vid_Save_in_CGRAM(void);
void LCD_vidGoTo(unsigned char col,unsigned char Row);
void LCD_SEND_number(int number);
void LCD_SEND_number_binary(int number);
void LCD_SEND_number_hex(unsigned char number);



#endif /* LCD_H_ */

/*
 * UART.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Nmr
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include<avr/interrupt.h>
#include<stdlib.h>



#define FOSC 8000000// Clock Speed
#define BAUD 115200

void (*call_back_pointer)(void);

void init_UART_9600(void);
void De_init_UART(void);
void init_UART_115200(void);

void UART_SendChar(char data);
char UART_getChar(void);
void UART_SEND_string(char *array);
void UART_SEND_number(int number);
void UART_set_call_back_function(void (*ptr)(void));



#endif /* UART_H_ */

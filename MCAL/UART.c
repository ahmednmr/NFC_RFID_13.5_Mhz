/*
 * UART.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Nmr
 */

#include "UART.h"



void init_UART_9600(void)
{

	//	    UCSRA= (1<<U2X);
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
	UBRRL =51;// 8;
	UBRRH =0;
}

void De_init_UART(void)
{

	UCSRA= 0;
	UCSRB = 0;
	UCSRC = 0;
	UBRRL =0;
	UBRRH =0;
}

void init_UART_115200(void)
{

	UCSRA= (1<<U2X);
	UCSRB = (1 << RXEN) | (1 << TXEN)|(1<<RXCIE);
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
	UBRRL =16;
	UBRRH =0;
}

void UART_SendChar(char data)
{
	while (!( UCSRA & (1<<UDRE))) ;  /* Wait for empty transmit buffer */

	UDR = data;                     /* Put data into buffer, sends the data */
}


char UART_getChar(void)
{
	while (!(UCSRA & (1<<RXC)));   /* Wait until reveived flag set */

	return UDR;                   /* Return data in received buffer */
}


void UART_SEND_string(char *array)
{
	int i=0;
	while(array[i]!='\0')
	{

		UART_SendChar(array[i]);
		i++;
	}

}



void UART_SEND_number(int number)
{
	char buffer[20];

	itoa(number,buffer,10);
	UART_SEND_string(buffer);


}




void UART_set_call_back_function(void (*ptr)(void))
{

	call_back_pointer=ptr;

}



ISR (USART_RXC_vect)
{

	call_back_pointer();

}



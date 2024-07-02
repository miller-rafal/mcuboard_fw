#include "usart.h"

void usart_initialize(unsigned int baudrate)
{
    // calculate ubrr
	unsigned int ubrr = (F_CPU / 8 / baudrate - 1) / 2;

	// set baud rate
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;

	// enable transmitter
	UCSRB |= (1 << TXEN);

    // enable receiver
	UCSRB |= (1 << RXEN);

	// set frame format: 8 data bits, 1 stop bit, even parity
	UCSRC |= (1 << URSEL) | (3 << UCSZ0) | (1 << UPM1);
}

void usart_transmit(unsigned char data)
{
	while(!(UCSRA & (1 << UDRE)));
	UDR = data;
}

unsigned char usart_receive(void)
{
	while(!(UCSRA & (1 << RXC)));
	return UDR;
}
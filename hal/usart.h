#ifndef USART_H
#define USART_H

#include <avr/io.h>

void usart_initialize(unsigned int baudrate);
void usart_transmit(unsigned char data);
unsigned char usart_receive(void);

#endif
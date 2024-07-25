#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

void spi_initialize(void);
void spi_transmit(unsigned char data);

#endif
#include "spi.h"

/*
    SPI clock rate enum?
*/

void spi_initialize(void)
{
    // set MOSI and SCK pins as output
    DDRB |= (1 << PB5) | (1 << PB7);

    // ensure MISO pin is set as input
    DDRB &= ~(1 << PB6);

    // enable SPI in master mode
    SPCR |= (1 << SPE) | (1 << MSTR);
    
    // set clock rate fck/16
    SPCR |= (1 << SPR0);
}

void spi_transmit(unsigned char data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
}
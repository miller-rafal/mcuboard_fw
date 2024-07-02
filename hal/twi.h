#ifndef TWI_H
#define TWI_H

#include <avr/io.h>
#include <util/twi.h>

#define TWI_READ    TW_READ
#define TWI_WRITE   TW_WRITE

// TODO - add more possible frequencies
typedef enum TwiSclFrequencyE
{
    TWI_SCL_FREQUENCY_100_KHZ = 72,
} TwiSclFrequencyE;

void twi_initialize(TwiSclFrequencyE scl_frequency);
int twi_start(void);
void twi_stop(void);
int twi_write_sla_rw(unsigned char address, unsigned char rw);
int twi_write(unsigned char data);
int twi_read_ack(unsigned char *output_p);
int twi_read_nack(unsigned char *output_p);

#endif
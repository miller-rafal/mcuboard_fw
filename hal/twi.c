#include "twi.h"

void twi_initialize(TwiSclFrequencyE scl_frequency)
{
    // set SDA and SCL pins as outputs
    DDRC |= (1 << PC0) | (1 << PC1);

    // pull-up SDA and SCL pins
    PORTC |= (1 << PC0) | (1 << PC1);

    // set SCL frequency
    TWBR = scl_frequency;
}

int twi_start(void)
{
    // send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // wait for TWINT flag set (START condition transmitted)
    while (!(TWCR & (1 << TWINT)));

    // check status
    if (TW_STATUS != TW_START && TW_STATUS != TW_REP_START)
    {
        return -1;
    }

    return 0;
}

void twi_stop(void)
{
    // send STOP condition
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

    // wait for TWSTO bit to be cleared (STOP condition transmitted)
    while ((TWCR & (1 << TWSTO)));
}

int twi_write(unsigned char data)
{
    // load data into TWDR register
    TWDR = data;

    // clear TWINT bit in TWCR to start transmission
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wait for TWINT flag set (data transmitted)
    while (!(TWCR & (1 << TWINT)));

    // check status
    if (TW_STATUS != TW_MT_DATA_ACK)
    {
        return -1;
    }

    return 0;
}

int twi_write_sla_rw(unsigned char address, unsigned char rw)
{
    // build data byte to send
    unsigned char data = address | rw;

    // load data into TWDR register
    TWDR = data;

    // clear TWINT bit in TWCR to start transmission
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wait for TWINT flag set (data transmitted)
    while (!(TWCR & (1 << TWINT)));

    // check status
    if (TW_STATUS != TW_MT_SLA_ACK && TW_STATUS != TW_MR_SLA_ACK)
    {
        return -1;
    }

    return 0;
}

// TODO - fix this function
int twi_read_ack(unsigned char *output_p)
{
    // clear TWINT bit in TWCR to start reception, enable ACK
    TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWEA));

    // wait for TWINT flag set (data received)
    while (!(TWCR & (1 << TWINT))); // TODO - seems to hang on this loop

    // check status
    if (TW_STATUS != TW_MR_DATA_ACK)
    {
        return -1;
    }

    // write data from TWDR register
    *output_p = TWDR;

    return 0;
}

int twi_read_nack(unsigned char *output_p)
{
    // clear TWINT bit in TWCR to start reception
    TWCR = ((1 << TWINT) | (1 << TWEN));

    // wait for TWINT flag set (data received)
    while (!(TWCR & (1 << TWINT)));
    
    // check status
    if (TW_STATUS != TW_MR_DATA_NACK)
    {
        return -1;
    }

    // write data from TWDR register
    *output_p = TWDR;

    return 0;
}
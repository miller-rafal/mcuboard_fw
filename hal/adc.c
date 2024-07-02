#include "adc.h"

void adc_initialize(unsigned char channel)
{
    // set selected channel as input -> DOES THIS WORK??
    DDRA &= ~channel;

    // set prescaler division factor to 128
    // 16 MHz / 128 = 125 kHz (recommended range is 50-200 kHz)
    ADCSRA |= 0x07;

    // set reference voltage to default value
    adc_set_reference_voltage(ADC_REFERENCE_VOLTAGE_AVCC);

    // enable ADC
    ADCSRA |= (1 << ADEN);
}

void adc_set_reference_voltage(AdcReferenceVoltageE reference_voltage)
{
    reference_voltage &= 0xc0;
    ADMUX |= reference_voltage;
}

unsigned short adc_read(unsigned char channel)
{
    channel &= 0x1f;   // apply bitmask to ensure only channel selection bits are affected
    ADMUX |= channel;  // set channel and gain

    ADCSRA |= (1 << ADSC);          // start conversion
    while(!(ADCSRA & (1 << ADIF))); // wait for conversion to finish (ADC interrupt flag set)
    ADCSRA |= (1 << ADIF);          // clear ADC interrupt flag

    ADMUX &= ~0x1f; // clear channel selection bits
    
    return ADC;
}
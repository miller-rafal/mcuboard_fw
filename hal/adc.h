#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

/*
    ADC channel definitions for single ended input
*/
#define ADC0    PA0
#define ADC1    PA1
#define ADC2    PA2
#define ADC3    PA3
#define ADC4    PA4
#define ADC5    PA5
#define ADC6    PA6
#define ADC7    PA7

typedef enum AdcReferenceVoltageE
{
    ADC_REFERENCE_VOLTAGE_AREF = 0,
    ADC_REFERENCE_VOLTAGE_AVCC = 64,
    ADC_REFERENCE_VOLTAGE_2V56 = 192
} AdcReferenceVoltageE;

void adc_initialize(unsigned char channel);
void adc_set_reference_voltage(AdcReferenceVoltageE reference_voltage);
unsigned short adc_read(unsigned char channel);

#endif
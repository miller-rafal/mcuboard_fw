#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

/*
    Channel definitions for non-inverting, fast PWM
*/
#define OC0     PB3
#define OC1A    PD5
#define OC1B    PD4
#define OC2     PD7

/*
    fPWM = fclk_IO / (PRESCALER * (1 + TOP))
*/
typedef enum PwmFrequencyE
{
    PWM_FREQUENCY_62K500_HZ,    // prescaler 1
    PWM_FREQUENCY_7K800_HZ,     // prescaler 8
    PWM_FREQUENCY_1K900_HZ,     // prescaler 32
    PWM_FREQUENCY_976_HZ,       // prescaler 64
    PWM_FREQUENCY_488_HZ,       // prescaler 128
    PWM_FREQUENCY_244_HZ,       // prescaler 256
    PWM_FREQUENCY_61_HZ         // prescaler 1024
} PwmFrequencyE;

void pwm_initialize(unsigned char channel);
int pwm_set_frequency(unsigned char channel, PwmFrequencyE frequency);
void pwm_set_duty_cycle(unsigned char channel, unsigned char duty_cycle);

#endif

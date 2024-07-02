#include "pwm.h"

static int set_prescaler(unsigned char channel, unsigned short value);
static int set_resolution(unsigned char channel, unsigned char value);

void pwm_initialize(unsigned char channel)
{
    switch (channel)
    {
        case OC0:
            DDRB |= (1 << OC0); // set OC0 as output       
            TCCR0 |= (1 << WGM01) | (1 << WGM00); // fast PWM
            TCCR0 |= (1 << COM01);  // clear OC0 on compare match (non-inverting mode)
            pwm_set_frequency(OC0, PWM_FREQUENCY_61_HZ);
            break;
        case OC1A:
            break;
        case OC1B:
            break;
        case OC2:
            DDRD |= (1 << OC2); // set OC2 as output
            TCCR2 |= (1 << WGM21) | (1 << WGM20); // fast PWM
            TCCR2 |= (1 << COM21); // clear OC2 on compare match (non-inverting mode)
            pwm_set_frequency(OC2, PWM_FREQUENCY_61_HZ);
            break;
        default:
            break;
    }
}

/*
    fPWM = fclk_IO / (PRESCALER * (1 + TOP))
*/
int pwm_set_frequency(unsigned char channel, PwmFrequencyE frequency)
{
    if (channel == OC0)
    {
        switch (frequency)
        {
            case PWM_FREQUENCY_62K500_HZ:
                set_prescaler(OC0, 1);
                break;
            case PWM_FREQUENCY_7K800_HZ:
                set_prescaler(OC0, 8);
                break;
            case PWM_FREQUENCY_976_HZ:
                set_prescaler(OC0, 64);
                break;
            case PWM_FREQUENCY_244_HZ:
                set_prescaler(OC0, 256);
                break;
            case PWM_FREQUENCY_61_HZ:
                set_prescaler(OC0, 1024);
                break;
            default:
                return -1; // invalid PWM frequency for this channel
        }
    }

    if (channel == OC1A)
    {
        return -1;
    }

    if (channel == OC1B)
    {
        return -1;
    }

    if (channel == OC2)
    {
        switch (frequency)
        {
            case PWM_FREQUENCY_62K500_HZ:
                set_prescaler(OC2, 1);
                break;
            case PWM_FREQUENCY_7K800_HZ:
                set_prescaler(OC2, 8);
                break;
            case PWM_FREQUENCY_1K900_HZ:
                set_prescaler(OC2, 32);
                break;
            case PWM_FREQUENCY_976_HZ:
                set_prescaler(OC2, 64);
                break;
            case PWM_FREQUENCY_488_HZ:
                set_prescaler(OC2, 128);
                break;
            case PWM_FREQUENCY_244_HZ:
                set_prescaler(OC2, 256);
                break;
            case PWM_FREQUENCY_61_HZ:
                set_prescaler(OC2, 1024);
                break;
            default:
                return -1; // invalid PWM frequency for this channel
        }
    }

    return -1; // invalid channel
}

void pwm_set_duty_cycle(unsigned char channel, unsigned char duty_cycle)
{
    switch (channel)
    {
        case OC0:
            OCR0 = duty_cycle;
            break;
        case OC1A:
            break;
        case OC1B:
            break;
        case OC2:
            OCR2 = duty_cycle;
            break;
        default:
            break;
    }
}

static int set_prescaler(unsigned char channel, unsigned short value)
{
    if (channel == OC0)
    {
        switch (value)
        {
            case 1:
                TCCR0 |= (1 << CS00);
                break;
            case 8:
                TCCR0 |= (1 << CS01);
                break;
            case 64:
                TCCR0 |= (1 << CS01) | (1 << CS00);
                break;
            case 256:
                TCCR0 |= (1 << CS02);
                break;
            case 1024:
                TCCR0 |= (1 << CS02) | (1 << CS00);
                break;
            default:
                return -1; // invalid value
        }

        return 0;
    }
    
    if (channel == OC1A)
    {
        // not implemented
        return -1;
    }
    
    if (channel == OC1B)
    {
        // not implemented
        return -1;
    }
    
    if (channel == OC2)
    {
        switch (value)
        {
            case 1:
                TCCR2 |= (1 << CS20);
                break;
            case 8:
                TCCR2 |= (1 << CS21);
                break;
            case 32:
                TCCR2 |= (1 << CS21) | (1 << CS20);
                break;
            case 64:
                TCCR2 |= (1 << CS22);
                break;
            case 128:
                TCCR2 |= (1 << CS22) | (1 << CS20);
                break;
            case 256:
                TCCR2 |= (1 << CS22) | (1 << CS21);
                break;
            case 1024:
                TCCR2 |= (1 << CS22) | (1 << CS21) | (1 << CS20);
                break;
            default:
                return -1; // invalid value
        }

        return 0;
    }

    // invalid channel
    return -1;
}

static int set_resolution(unsigned char channel, unsigned char value)
{
    if (channel == OC1A)
    {
        return -1; // not implemented
    }

    if (channel == OC1B)
    {
        return -1; // not implemented
    }

    // invalid channel
    return -1;
}
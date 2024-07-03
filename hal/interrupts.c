#include "interrupts.h"

static void (*int0_callback)(void);
static void (*int1_callback)(void);
static void (*int2_callback)(void);

ISR(INT0_vect)
{
    int0_callback();
}

ISR(INT1_vect)
{
    int1_callback();
}

ISR(INT2_vect)
{
    int2_callback();
}

void interrupts_register_int0(InterruptSenseControlE sense_control, void (*callback)(void))
{
    GICR |= (1 << INT0);
    MCUCR = (MCUCR & 0b11111100) | sense_control;

    int0_callback = callback;
}

void interrupts_unregister_int0(void)
{
    GICR &= ~(1 << INT0);
    MCUCR = (MCUCR & 0b11111100);
}

void interrupts_register_int1(InterruptSenseControlE sense_control, void (*callback)(void))
{
    GICR |= (1 << INT1);
    MCUCR = (MCUCR & 0b11110011) | (sense_control << 2);

    int1_callback = callback;
}

void interrupts_unregister_int1(void)
{
    GICR &= ~(1 << INT1);
    MCUCR = (MCUCR & 0b11110011);
}

int interrupts_register_int2(InterruptSenseControlE sense_control, void (*callback)(void))
{
    if ((sense_control != INTERRUPT_SENSE_FALLING_EDGE) &&
        (sense_control != INTERRUPT_SENSE_RISING_EDGE))
    {
        return -1;
    }

    GICR |= (1 << INT2);

    if (sense_control == INTERRUPT_SENSE_RISING_EDGE)
    {
        MCUCSR |= (1 << ISC2);
    }
    else
    {
        MCUCSR &= ~(1 << ISC2);
    }

    int2_callback = callback;

    return 0;
}

void interrupts_unregister_int2(void)
{
    GICR &= ~(1 << INT2);
    MCUCSR &= ~(1 << ISC2);
}
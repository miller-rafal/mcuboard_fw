#include "interrupts.h"

static void (*int0_callback)(void);
static void (*int1_callback)(void);

ISR(INT0_vect)
{
    int0_callback();
}

ISR(INT1_vect)
{
    int1_callback();
}

void interrupts_register_int0(InterruptSenseControlE sense_control, void (*callback)(void))
{
    GICR |= (1 << INT0);
    MCUCR |= sense_control;

    int0_callback = callback;
}

void interrupts_register_int1(InterruptSenseControlE sense_control, void (*callback)(void))
{
    GICR |= (1 << INT1);
    MCUCR |= (sense_control << 2);

    int1_callback = callback;
}
#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum InterruptSenseControlE
{
    INTERRUPT_SENSE_LOW_LEVEL,
    INTERRUPT_SENSE_ANY_CHANGE,
    INTERRUPT_SENSE_FALLING_EDGE,
    INTERRUPT_SENSE_RISING_EDGE
} InterruptSenseControlE;

void interrupts_register_int0(InterruptSenseControlE sense_control, void (*callback)(void));
void interrupts_unregister_int0(void);

void interrupts_register_int1(InterruptSenseControlE sense_control, void (*callback)(void));
void interrupts_unregister_int1(void);

int interrupts_register_int2(InterruptSenseControlE sense_control, void (*callback)(void));
void interrupts_unregister_int2(void);

#endif
#include <avr/io.h>
#include <util/delay.h>

#include "printing.h"

int main(void)
{
    DDRD |= (1 << PD7);
    PORTD &= ~(1 << PD7);

    printing_initialize();

    while(1)
    {
        PORTD |= (1 << PD7);
        printf("LED on\n");
        _delay_ms(1000);
        PORTD &= ~(1 << PD7);
        printf("LED off\n");
        _delay_ms(1000);
    }

    return 0;
}

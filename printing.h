#include <stdio.h>

#include "hal/usart.h"

int transmit(char c, FILE *stream)
{
    usart_transmit(c);
    return 0;
}

FILE print_file = FDEV_SETUP_STREAM(transmit, NULL, _FDEV_SETUP_WRITE);

void printing_initialize(void)
{
    usart_initialize(9600);

    stdout = &print_file;
    stderr = &print_file;
}
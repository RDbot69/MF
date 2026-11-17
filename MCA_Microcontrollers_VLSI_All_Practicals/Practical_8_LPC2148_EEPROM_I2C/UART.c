#include <stdio.h>
#include <lpc214x.h>
#include "UART.h"

void UartInit(unsigned int baudrate)
{
    unsigned int FDiv;
    PINSEL0 &= 0xFFFFFFF0;
    PINSEL0 |= 0x00000005;

    U0LCR = 0x83;
    U0FDR = 0x10;
    FDiv = (15000000 / 16) / baudrate;
    U0DLM = FDiv / 256;
    U0DLL = FDiv % 256;
    U0LCR = 0x03;
    U0TER = 0x80;
}

int UART_GetChar(void)
{
    while (!(U0LSR & 0x01));
    return U0RBR;
}

int UART_PutChar(unsigned char Ch)
{
    if (Ch == '\n')
    {
        while (!(U0LSR & 0x20));
        U0THR = 0x0D;
    }
    while (!(U0LSR & 0x20));
    return (U0THR = Ch);
}

int fputc(int ch, FILE *f)
{
    return UART_PutChar(ch);
}

struct __FILE { int handle; };
FILE __stdout;

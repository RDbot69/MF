#include <lpc214x.h>
#include <stdio.h>

void UartInit(unsigned int baudrate)
{
    int i, FDiv;
    i = PINSEL0;
    i = i & 0xFFF0FFF0;
    PINSEL0 = (i | 0x50005);      // Configure TxD and RxD pins

    U0LCR = 0x83;                 // DLAB=1, 8 data bits, 1 stop bit, no parity
    FDiv = (15000000 / 16) / baudrate;
    U0DLM = FDiv / 256;
    U0DLL = FDiv % 256;
    U0LCR = 0x03;                 // DLAB=0
    U0TER = 0x80;
}

int UART_GetChar(void)
{
    while (!(U0LSR & 0x01));
    return U0RBR;
}

int UART_PutChar(unsigned char ch)
{
    while (!(U0LSR & 0x20));
    if (ch == '\n')
        ch = 0x0D;
    U0THR = ch;
    return ch;
}

int fputc(int ch, FILE *f)
{
    return UART_PutChar(ch);
}

struct __FILE { int handle; };
FILE __stdout;

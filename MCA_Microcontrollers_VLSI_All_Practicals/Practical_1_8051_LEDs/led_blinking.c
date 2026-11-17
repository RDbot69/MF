#include <reg51.h>

void delay(void);

void main(void)
{
    while (1)
    {
        P2 = 0xFF;       // All LEDs ON (11111111)
        delay();
        P2 = 0x00;       // All LEDs OFF (00000000)
        delay();
    }
}

void delay(void)
{
    int i, j;
    for (i = 0; i < 500; i++)
    {
        for (j = 0; j < 1000; j++);
    }
}

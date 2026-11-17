#include <reg51.h>

void delay(void)
{
    int i;
    for (i = 0; i < 50000; i++);
}

void main(void)
{
    while (1)
    {
        P2 = 0xAA;       // 10101010
        delay();
        P2 = 0x55;       // 01010101
        delay();
    }
}

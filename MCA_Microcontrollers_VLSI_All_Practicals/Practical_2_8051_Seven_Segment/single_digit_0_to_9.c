#include <reg51.h>

void delay(void)
{
    int i, j;
    for (i = 0; i < 500; i++)
    {
        for (j = 0; j < 100; j++)
        {
        }
    }
}

void main(void)
{
    int seg_code[10] = {
        0xC0, 0xF9, 0xA4, 0xB0, 0x99,
        0x92, 0x82, 0xF8, 0x80, 0x90
    };
    int k;

    while (1)
    {
        for (k = 0; k < 10; k++)
        {
            P1 = seg_code[k];
            P2 = 0x01;
            delay();
        }
    }
}

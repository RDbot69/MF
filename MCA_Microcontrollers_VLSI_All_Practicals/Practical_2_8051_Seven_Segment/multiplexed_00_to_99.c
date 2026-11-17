#include <reg51.h>

#define seg_unit 0x08
#define seg_tens 0x04

void delay(void)
{
    int i, j;
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 10; j++);
    }
}

void main(void)
{
    int seg_code[10] = {
        0xC0, 0xF9, 0xA4, 0xB0, 0x99,
        0x92, 0x82, 0xF8, 0x80, 0x90
    };
    int cnt, temp, i, num;

    while (1)
    {
        for (cnt = 0; cnt <= 99; cnt++)
        {
            for (i = 0; i < 100; i++)
            {
                num = cnt;
                temp = num % 10;
                P2 = seg_unit;
                P1 = seg_code[temp];
                delay();

                num = cnt;
                temp = num / 10;
                P2 = seg_tens;
                P1 = seg_code[temp];
                delay();
            }
        }
    }
}

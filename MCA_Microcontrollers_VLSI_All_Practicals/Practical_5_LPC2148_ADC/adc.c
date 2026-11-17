#include <lpc214x.h>

void ADCInit(void)
{
    PINSEL1 &= 0xF0FFFFFF;       // Configure P0.28 and P0.29 as ADC pins
    PINSEL1 |= 0x05000000;
}

unsigned int ADC_Read(unsigned char channel)
{
    static unsigned int ad1_data;

    AD0CR = 0x00200300 | (1 << channel);  // Burst off, clock divider, channel, 10-bit ADC
    AD0CR |= (1 << 24);                   // Start ADC

    while (!(AD0GDR & 0x80000000));       // Wait for DONE bit

    ad1_data = (AD0GDR & 0x0000FFC0) >> 6;
    return ad1_data;
}

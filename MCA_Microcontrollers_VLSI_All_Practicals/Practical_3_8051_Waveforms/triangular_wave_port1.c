#include <reg51.h>

void delay(void);

void main(void)
{
    int i, j;

    while (1)
    {
        // Increase value from 0 to 255
        for (i = 0; i <= 255; i++)
        {
            P1 = i;      // Send increasing value to Port 1
            delay();     // Small delay
        }

        // Decrease value from 255 to 0
        for (j = 255; j >= 0; j--)
        {
            P1 = j;      // Send decreasing value to Port 1
            delay();     // Small delay
        }
    }
}

// The supplied triangular-wave listing declares delay() but does not define it.
// This uses the Timer 0 delay function shown with the square-wave listing.
void delay(void)
{
    TMOD = 0x01;
    TL0 = 0x01;
    TH0 = 0xFF;
    TR0 = 1;
    while (TF0 == 0);
    TR0 = 0;
    TF0 = 0;
}

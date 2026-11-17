#include <lpc214x.h>
#include <stdio.h>

#define RTConPrescaler 1   // 1: use PCLK prescaler; 0: use external oscillator
extern void UartInit(unsigned int);

void delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 5000; j++);
}

void RTCInit(void)
{
    CIIR = 0x00;            // No interrupt generated
#ifdef RTConPrescaler
    PREINT = 0x16D;         // Assuming 15 MHz PCLK
    PREFRAC = 0x1B00;       // Assuming 15 MHz PCLK
    CCR = 0x02;
#else
    CCR = 0x02;
#endif
}

void SetTime(int hours, int mins, int sec)
{
    SEC = sec;
    MIN = mins;
    HOUR = hours;
    CCR = 0x01;             // Start the clock
}

int main(void)
{
    UartInit(9600);
    RTCInit();
    SetTime(5, 30, 1);

    while (1)
    {
        printf("\nThe Time is ");
        printf(":%02d", HOUR);
        printf(":%02d", MIN);
        printf(":%02d", SEC);
        delay(500);
    }

    return 0;
}

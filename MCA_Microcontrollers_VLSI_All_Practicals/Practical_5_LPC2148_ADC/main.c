#include "adc.h"
#include "LCD.h"
#include <stdio.h>

void delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 5000; j++);
}

int main(void)
{
    unsigned int temp;
    char buf[16];

    LCD_init();
    ADCInit();

    while (1)
    {
        temp = ADC_Read(1);                   // Read AN0.1 / AD0.1
        sprintf(buf, "ADC result:0x%03X", temp);
        LCD_display(1, 1, buf);
        delay(20);
    }
}

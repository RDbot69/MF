#include <lpc214x.h>
#include "UART.h"
#include "I2C.h"
#include "EEPROM.h"
#include <stdio.h>

unsigned char write_array[10] = {
    0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0xC5
};
unsigned char read_array[10];

int main(void)
{
    unsigned int i;

    PINSEL2 = 0;             // LED init
    IODIR1 = 0xFF000000;
    IOCLR1 = 0xFF << 24;

    UartInit(9600);
    printf("I2C EEPROM\r\n");
    I2CInit();

    printf("Writing Data.....\r\n");
    EEPROM_write(0x1349, write_array, 10);

    printf("Reading Data.....\r\n");
    EEPROM_read(0x1349, read_array, 10);

    for (i = 0; i < 10; i++)
    {
        printf("write_array[%d] = 0x%02X\tread_array[%d] = 0x%02X\r\n",
               i, write_array[i], i, read_array[i]);
    }

    IOSET1 = read_array[9] << 24;
    while (1);              // Stop here forever
}

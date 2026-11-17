#include "I2C.h"

#define EEPROM_Addr 0xA0

void EEPROM_write(unsigned int add, unsigned char *data, unsigned char len)
{
    unsigned char i;

    I2CStart();
    I2Csend(EEPROM_Addr | I2Cwrite);
    I2Csend(add >> 8);
    I2Csend(add & 0xFF);

    for (i = 0; i < len; i++)
        I2Csend(*data++);

    I2CStop();
}

void EEPROM_read(unsigned int add, unsigned char *data, unsigned char len)
{
    unsigned char i;

    I2CStart();
    I2Csend(EEPROM_Addr | I2Cwrite);
    I2Csend(add >> 8);
    I2Csend(add & 0xFF);
    I2CStart();
    I2Csend(EEPROM_Addr | I2Cread);

    for (i = 0; i < len; i++)
        *data++ = I2Cget();

    I2CStop();
}

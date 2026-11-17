#include <lpc214x.h>

#define I2C_ENABLE (1 << 6)
#define I2C_START  (1 << 5)
#define I2C_STOP   (1 << 4)
#define I2C_SI     (1 << 3)
#define I2C_AACK   (1 << 2)

void I2CInit(void)
{
    PINSEL0 &= 0xFFFFFF0F;
    PINSEL0 |= 0x00000050;     // P0.2 = SCL0, P0.3 = SDA0

    I2C0CONCLR = I2C_ENABLE | I2C_START | I2C_STOP | I2C_SI | I2C_AACK;
    I2C0SCLH = 0x4B;
    I2C0SCLL = 0x4B;
    I2C0CONSET = I2C_ENABLE;
}

void I2CStart(void)
{
    unsigned int status;

    I2C0CONCLR = I2C_START | I2C_STOP | I2C_SI | I2C_AACK;
    I2C0CONSET = I2C_ENABLE;
    I2C0CONSET = I2C_START;
    while (!((status = I2C0CONSET) & I2C_SI));
}

void I2CStop(void)
{
    I2C0CONCLR = I2C_START | I2C_SI | I2C_AACK;
    I2C0CONSET = I2C_STOP;
}

void I2Csend(unsigned char data)
{
    unsigned int status;
    I2C0DAT = data;
    I2C0CONCLR = I2C_START | I2C_STOP;
    I2C0CONCLR = I2C_SI;
    while (!((status = I2C0CONSET) & I2C_SI));
}

unsigned char I2Cget(void)
{
    unsigned char data;
    unsigned int status;

    I2C0CONCLR = I2C_START | I2C_STOP;
    I2C0CONCLR = I2C_SI;
    I2C0CONSET = I2C_AACK;
    while (!((status = I2C0CONSET) & I2C_SI));
    data = I2C0DAT;
    return data;
}

#include <lpc214x.h>
#include "LCD.h"

#define LCD_DATAMASK 0x000000FF
#define LCD_PORT 0x000FF000
#define LCD_SHIFT 12
#define LCD_RS (1 << 20)
#define LCD_EN (1 << 21)

void LCD_delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 500; j++);
}

void SendInstruction(unsigned int command)
{
    command &= LCD_DATAMASK;
    command = command << LCD_SHIFT;

    IOCLR1 = LCD_RS;
    LCD_delay(10);
    IOSET1 = LCD_EN;
    LCD_delay(10);
    IOCLR0 = LCD_PORT;
    IOSET0 = command;
    LCD_delay(10);
    IOCLR1 = LCD_EN;
    LCD_delay(10);
    IOCLR1 = LCD_RS;
    IOCLR1 = LCD_DATAMASK << LCD_SHIFT;
}

void SendData(unsigned int lcddata)
{
    lcddata &= LCD_DATAMASK;
    lcddata = lcddata << LCD_SHIFT;

    IOSET1 = LCD_RS;
    LCD_delay(10);
    IOSET1 = LCD_EN;
    LCD_delay(10);
    IOCLR0 = LCD_PORT;
    IOSET0 = lcddata;
    LCD_delay(10);
    IOCLR1 = LCD_EN;
    LCD_delay(10);
    IOCLR1 = LCD_RS;
    IOCLR1 = LCD_DATAMASK << LCD_SHIFT;
}

void SetLineNumber(unsigned int linenum)
{
    if (linenum == 1)
        SendInstruction(SETDDRAMADDR | 0x00);
    else
        SendInstruction(SETDDRAMADDR | 0x40);
}

void SetAddress(unsigned char memory, unsigned int address)
{
    address &= 0x0000007F;
    if (memory == DDRAM)
        SendInstruction(SETDDRAMADDR | address);
    else
        SendInstruction(SETCGRAMADDR | address);
}

void BlinkDisplay(void)
{
    SendInstruction(DISPONOFFCTRL);
    LCD_delay(500);
    SendInstruction(DISPONOFFCTRL | DISPLAY_ON | CURSOR_ON | BLINKCHAR_ON);
    LCD_delay(500);
}

void ShiftDisplay(unsigned char direction, unsigned int clicks)
{
    unsigned int i;
    if (direction == RIGHTSHIFT)
    {
        for (i = 0; i < clicks; i++)
            SendInstruction(DISPCURSHIFT | SHIFTRIGHT);
    }
    else
    {
        for (i = 0; i < clicks; i++)
            SendInstruction(DISPCURSHIFT);
    }
}

void ClearDisplay(void)
{
    SendInstruction(CLEARDISPLAY);
}

void InitLCD(void)
{
    unsigned int temp;
    temp = PINSEL2;
    temp &= 0xFFFFFFF7;
    PINSEL2 = 0;
    IODIR1 = LCD_RS | LCD_EN;
    IODIR0 = 0x000FF000;

    SendInstruction(FUNCTIONSET | FS_DATALENGTH);
    LCD_delay(5);
    SendInstruction(FUNCTIONSET | FS_DATALENGTH);
    LCD_delay(1);
    SendInstruction(FUNCTIONSET | FS_DATALENGTH | FS_LINES2);
    SendInstruction(DISPONOFFCTRL);
    SendInstruction(CLEARDISPLAY);
    SendInstruction(ENTRYMODESET | ENTRYMODESET_INC);
    SendInstruction(DISPONOFFCTRL | DISPLAY_ON | CURSOR_ON);
}

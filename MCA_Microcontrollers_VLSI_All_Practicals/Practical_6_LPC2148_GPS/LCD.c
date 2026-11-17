#include <lpc214x.h>

#define LCD_PORT 0x00FF0000
#define EN (1 << 10)
#define RS (1 << 11)
#define RW (1 << 20)
#define LCD_SHIFT 16

void delay(unsigned int time)
{
    int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 200; j++);
}

void LCD_strobe(void)
{
    delay(100);
    IOSET0 = EN;
    delay(100);
    IOCLR0 = EN;
    delay(100);
}

void LCD_data(unsigned char ch)
{
    IOCLR1 = LCD_PORT;
    IOSET1 = ch << LCD_SHIFT;
    IOSET0 = RS;
    IOCLR0 = RW;
    LCD_strobe();
}

void LCD_cmd(unsigned char ch)
{
    IOCLR1 = LCD_PORT;
    IOSET1 = ch << LCD_SHIFT;
    IOCLR0 = RS;
    IOCLR0 = RW;
    LCD_strobe();
}

void LCD_init(void)
{
    PINSEL0 &= 0xFF0FFFFF;
    PINSEL1 &= 0xFFFFFCFF;
    PINSEL2 &= 0xFFFFFFF3;

    IODIR0 |= RS | EN | RW;
    IODIR1 |= LCD_PORT;

    LCD_cmd(0x38);
    LCD_cmd(0x06);
    LCD_cmd(0x0C);
    LCD_cmd(0x01);
    LCD_cmd(0x80);
}

void LCD_display(int row, int pos, unsigned char *ch)
{
    unsigned char temp;
    if (row == 1)
        temp = 0x80 | (pos - 1);
    else
        temp = 0xC0 | (pos - 1);

    LCD_cmd(temp);
    while (*ch)
        LCD_data(*ch++);
}

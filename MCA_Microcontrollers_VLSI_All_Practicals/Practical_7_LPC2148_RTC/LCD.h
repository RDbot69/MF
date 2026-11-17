#ifndef LCD_H
#define LCD_H

// Commands for 16x2 character LCD
#define CLEARDISPLAY       0x01
#define RETURNHOME         0x02
#define ENTRYMODESET       0x04
#define DISPONOFFCTRL      0x08
#define DISPCURSHIFT       0x10
#define FUNCTIONSET        0x20
#define SETCGRAMADDR       0x40
#define SETDDRAMADDR       0x80
#define ENTRYMODESET_INC   0x02
#define ENTRYMODESET_DEC   0x04
#define ENTRYMODESET_SHIFT 0x01
#define DISPLAY_ON         0x04
#define CURSOR_ON          0x02
#define BLINKCHAR_ON       0x01
#define SHIFTCURSOR        0x08
#define SHIFTRIGHT         0x04
#define FS_DATALENGTH      0x10
#define FS_LINES2          0x08
#define FS_FONT            0x04
#define DDRAM              1
#define CGRAM              0
#define RIGHTSHIFT         1
#define LEFTSHIFT          0

void SendInstruction(unsigned int);
void SendData(unsigned int);
void InitLCD(void);
void SetLineNumber(unsigned int);
void SetAddress(unsigned char, unsigned int);
void BlinkDisplay(void);
void ShiftDisplay(unsigned char, unsigned int);
void RollDisplay(void);
void ClearDisplay(void);

#endif

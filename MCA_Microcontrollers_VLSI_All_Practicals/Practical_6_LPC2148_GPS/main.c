#include <lpc214x.h>
#include <stdio.h>
#include "lcd.h"
#include "UART.h"

/* Fetch characters from UART until the '*' terminator is received. */
void GPS_string(unsigned char *temp)
{
    unsigned int i = 0;
    do
    {
        temp[i] = UART_GetChar();
    }
    while (temp[i++] != '*');

    temp[i] = '\0';
}

/* Display latitude and longitude on the LCD. */
void GPS_display(unsigned char *lat, unsigned char *lon)
{
    unsigned int i;

    LCD_cmd(0x84);
    for (i = 0; i < 2; i++)
        LCD_data(*lat++);
    LCD_data('\'');
    LCD_data(*lat++);

    LCD_cmd(0xC4);
    for (i = 0; i < 3; i++)
        LCD_data(*lon++);
    LCD_data('\'');
    for (i = 0; i < 8; i++)
        LCD_data(*lon++);
}

int main(void)
{
    /* The supplied writeup declares temp[20]. See README for the buffer warning. */
    unsigned char ch, temp[20], lat[10], lon[10];
    unsigned int i = 0, j = 0;

    LCD_init();
    UartInit(9600);
    LCD_display(1, 1, "GPS Program");
    delay(200000);
    LCD_cmd(0x01);
    LCD_display(1, 1, "LAT:");
    LCD_display(2, 1, "LON:");

    while (1)
    {
        if ((ch = UART_GetChar()) == '$')
        {
            GPS_string(temp);

            if (temp[2] == 'G' && temp[3] == 'G' && temp[4] == 'A')
            {
                i = 0;
                j = 0;

                while (temp[i++] != ',');  // Ignore $GPGGA identifier
                while (temp[i++] != ',');  // Ignore time stamp

                while (temp[i] != ',')     // Capture latitude
                    lat[j++] = temp[i++];

                while (temp[i++] != ',');  // Ignore N/S field
                lat[j++] = temp[i++];      // Store N/S direction
                lat[j] = '\0';

                j = 0;
                while (temp[i++] != ',');

                while (temp[i] != ',')     // Capture longitude
                    lon[j++] = temp[i++];

                while (temp[i++] != ',');  // Ignore E/W field
                lon[j++] = temp[i++];      // Store E/W direction
                lon[j] = '\0';

                GPS_display(lat, lon);
            }
        }
    }

    return 0;
}

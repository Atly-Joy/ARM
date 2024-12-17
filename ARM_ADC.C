#include <LPC213X.H>
#include <string.h>
#include <stdio.h>

long i;
char chr[20]; // Increased buffer size for safety
int adcValue;

void data(unsigned char a);
void display(const char *p);
void cmd(unsigned char a);
void _delay_ms(long j);

int main(void) 
{
    // Pin Configuration
    IO0DIR = 0x000700ff;      // Set P0.0-P0.15 as output (for LCD data and control)
 
    // LCD Initialization
    cmd(0x38); // Function set: 2 lines, 5x7 matrix
    cmd(0x0C); // Display ON, Cursor OFF
    cmd(0x06); // Entry mode set: Increment cursor
    cmd(0x01); // Clear display

    // ADC Configuration
    AD0CR = (1 << 0)       // Select channel 0 (P0.27/AD0.0)
          | (3 << 8)       // CLKDIV: ADC clock = PCLK/4
          | (1 << 21);     // Power up ADC

    while (1) {
        // Start ADC Conversion
        AD0CR |= (1 << 24); // Start conversion
        while ((AD0GDR & (1 << 31)) == 0); // Wait for conversion to complete

        // Extract ADC Result (12-bit value)
        adcValue = (AD0GDR >> 6) & 0x3FF; // Bits 15:6 contain the result
        // Prepare and display the result
        sprintf(chr, "ADC Value: %4d", adcValue);
        cmd(0x01); // Clear display
        cmd(0x80); // Move cursor to beginning
        display(chr);
		_delay_ms(2);
    }
}

void cmd(unsigned char a )
{
	IOCLR0=0XFFFFF0FF;
    IOSET0=0x00040000;//RS=0,RW=0,E=1
    IOSET0=a;
    _delay_ms(1);
    IOCLR0=0x00040000;//RS=0,RW=0,E=0
    _delay_ms(3);
}
void data(unsigned char a )
{
	IOCLR0=0XFFFFF0FF;
    IOSET0=0x00050000;//RS=1,RW=0,E=1
    IOSET0=a;
    _delay_ms(1);
    IOCLR0=0x00040000;//RS=1,RW=0,E=0
    _delay_ms(3);
}

void display(const char *p)
{
    while(*p)
    {
        data(*p);
        p++;
    }
}
void _delay_ms(long j)
{
	long i;
    for(i=0;i<=j*1000;i++);
}
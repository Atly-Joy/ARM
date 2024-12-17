#include <lpc21xx.h>
#include <stdio.h>

void cmd(unsigned char a);
void data(unsigned char a);
void display(const char *p);
void _delay_ms(long j);
void rtc_get_time(char *time_str);
void rtc_init();

int main() {
    char time[10];
    IODIR0 = 0xFFFFFFFF;  // Configure Port 0 as output

    // Initialize LCD and RTC
    cmd(0x33);  // Initialize LCD in 4-bit mode
    cmd(0x32);  // Set 4-bit mode
    cmd(0x28);  // 2 lines, 5x7 matrix
    cmd(0x0F);  // Display ON, cursor ON
    cmd(0x06);  // Entry mode, auto increment
    cmd(0x01);  // Clear LCD
    _delay_ms(2); // Delay for command processing
	rtc_init();
	display("atly");
    while (1) 
	{
        cmd(0x80);  // Move cursor to the first line
        display("TIME:");
        rtc_get_time(time);
        cmd(0xC0);  // Move cursor to the second line
        display(time);
        _delay_ms(1000);  // Delay for 1 second
    }
}

void cmd(unsigned char a) {
    IOCLR0 = 0xFFFFFFFF;  // Clear D4-D7 and control bits
    IOSET0 = (a & 0xF0) << 4; // Send high nibble
    IOSET0 |= 0x00040000; // RS=0, RW=0, E=1
    _delay_ms(1);
    IOCLR0 = 0x00040000; // RS=0, RW=0, E=0
    _delay_ms(3);

    IOCLR0 = 0xFFFFFFFF;  // Clear D4-D7 and control bits
    IOSET0 = (a & 0x0F) << 8; // Send low nibble
    IOSET0 |= 0x00040000; // RS=0, RW=0, E=1
    _delay_ms(1);
    IOCLR0 = 0x00040000; // RS=0, RW=0, E=0
    _delay_ms(3);
}

void data(unsigned char a) {
    IOCLR0 = 0xFFFFFFFF;  // Clear D4-D7 and control bits
    IOSET0 = (a & 0xF0) << 4; // Send high nibble
    IOSET0 |= 0x00050000; // RS=1, RW=0, E=1
    _delay_ms(1);
    IOCLR0 = 0x00040000; // RS=1, RW=0, E=0
    _delay_ms(3);

    IOCLR0 = 0xFFFFFFFF;  // Clear D4-D7 and control bits
    IOSET0 = (a & 0x0F) << 8; // Send low nibble
    IOSET0 |= 0x00050000; // RS=1, RW=0, E=1
    _delay_ms(1);
    IOCLR0 = 0x00040000; // RS=1, RW=0, E=0
    _delay_ms(3);
}

void display(const char *p) {
    while (*p) {
        data(*p++);
    }
}

void _delay_ms(long j) {
    long i;
    for (i = 0; i <= j * 500; i++);
}

void rtc_init() {
	//CCR = 0x01;  // Enable the RTC
    CCR = 0x00;  // Disable the RTC to set time
    SEC = 30;    // Initialize seconds
    MIN = 30;     // Initialize minutes
    HOUR = 11;   // Initialize hours
    CCR = 0x01;  // Enable the RTC
}

void rtc_get_time(char *time_str) {
    unsigned int hour, min, sec;
    hour = HOUR;
    min = MIN;
    sec = SEC;
    sprintf(time_str, "%02u:%02u:%02u", hour, min, sec);
}


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

    cmd(0x0c);  // Display ON, cursor ON
    cmd(0x38);  // 8-bit mode, 2 lines
    cmd(0x80);  // Move cursor to the first line

    rtc_init(); // Initialize RTC

    while (1) {
        cmd(0x80);  // Move cursor to the first line
        display("TIME:");
        rtc_get_time(time);
        cmd(0xC0);  // Move cursor to the second line
        display(time);
        _delay_ms(10);  // Delay for 1 second

    }
}

void cmd(unsigned char a) {
    IOCLR0 = 0xFFFFFFFF;
    IOSET0 = 0x00040000; // RS=0, RW=0, E=1
    IOSET0 |= a;
    _delay_ms(1);
    IOCLR0 = 0x00040000; // RS=0, RW=0, E=0
    _delay_ms(3);
}

void data(unsigned char a) {
    IOCLR0 = 0xFFFFFFFF;
    IOSET0 = 0x00050000; // RS=1, RW=0, E=1
    IOSET0 |= a;
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
    CCR = 0x00;  // Disable the RTC to set time
    SEC = 30;    // Initialize seconds
    MIN = 47;    // Initialize minutes
    HOUR = 05;   // Initialize hours
    CCR = 0x11;  // Enable the RTC and reset counters
    //CCR = 0x01;  // Start the RTC
}

void rtc_get_time(char *time_str) {
    unsigned int hour, min, sec;
    hour = HOUR;
    min = MIN;
    sec = SEC;
    sprintf(time_str, "%02u:%02u:%02u", hour, min, sec);
}

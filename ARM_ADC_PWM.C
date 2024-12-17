#include <lpc213x.h>
#include <string.h>
#include <stdio.h>

long i;
char chr[20];  // Buffer for ADC value display
char chr1[20]; // Buffer for duty cycle display
unsigned int duty_cycle; // Duty cycle percentage
unsigned int adc_value;  // ADC read value
unsigned long temp;

// Function Prototypes
void data(unsigned char a);
void display(const char *p);
void cmd(unsigned char a);
void _delay_ms(long j);
void update_pwm_duty_cycle(unsigned int adc_value);
void pwm_init(void);
unsigned int read_adc(void);
void adc_init(void);

int main() {
    IO0DIR = 0xFFFFFFFF; // Configure necessary IO pins
    adc_init();
    pwm_init();

    // Initialize LCD
    cmd(0x38); // 2-line LCD, 5x7 matrix
    cmd(0x01); // Clear display
    cmd(0x0F); // Display ON, cursor ON
    cmd(0x80); // Move cursor to the beginning
    display("ATLY");

    while (1) 
	{
        adc_value = read_adc(); // Read ADC value
        duty_cycle = (adc_value * 100) / 1023; // Calculate duty cycle

        // Display ADC Value on LCD
        cmd(0x01); // Clear display
        cmd(0x80); // Move cursor to beginning
        sprintf(chr, "ADC Value: %4d", adc_value);
        display(chr);

        // Update PWM duty cycle
        update_pwm_duty_cycle(adc_value);

        // Display Duty Cycle on LCD
        cmd(0xC0); // Move cursor to second line
        sprintf(chr1, "DUTY CYCLE: %3d%%", duty_cycle);
        display(chr1);

        _delay_ms(200); // Small delay to stabilize display updates
    }
}

// Send Command to LCD
void cmd(unsigned char a) {
    IOCLR0 = 0xFFFFFFFF;    // Clear data lines
    IOSET0 = 0x00040000;    // RS=0, RW=0, E=1
    IOSET0 = a;             // Send command
    _delay_ms(1);
    IOCLR0 = 0x00040000;    // RS=0, RW=0, E=0
    _delay_ms(3);
}

// Send Data to LCD
void data(unsigned char a) {
    IOCLR0 = 0xFFFFFFFF;    // Clear data lines
    IOSET0 = 0x00050000;    // RS=1, RW=0, E=1
    IOSET0 = a;             // Send data
    _delay_ms(1);
    IOCLR0 = 0x00040000;    // RS=1, RW=0, E=0
    _delay_ms(3);
}

// Display String on LCD
void display(const char *p) {
    while (*p) {
        data(*p);
        p++;
    }
}

// Delay Function
void _delay_ms(long j) {
    long i;
    for (i = 0; i <= j * 1000; i++);
}

// Initialize ADC
void adc_init(void) {
    PINSEL1 |= (1 << 24); // Select AD0.1 (P0.28) as ADC function
    AD0CR = (1 << 1) |    // Select AD0.1 channel
            (4 << 8) |    // ADC clock divider
            (1 << 21);    // Enable ADC
}

// Read ADC Value
unsigned int read_adc(void) {
    AD0CR |= (1 << 24); // Start ADC conversion
    while ((AD0GDR & (1 << 31)) == 0); // Wait for conversion to complete
    return (AD0GDR >> 6) & 0x3FF; // Extract 10-bit result
}

// Initialize PWM
void pwm_init(void) {
    PINSEL2 |= (1 << 2);  // Set PWM5 on P0.21
    PWMMR0 = 1000;        // PWM period = 100 ms (100 * 1 ms)
    PWMMCR = 1 << 1;      // Reset on PWMMR0
    PWMTCR = 2;           // Counter reset
    PWMTCR = 1 | (1 << 3); // Counter enable and PWM enable
    PWMPR = 19999;        // 1 ms timer period
    PWMPCR = 1 << 13;     // Enable PWM5 output
}

// Update PWM Duty Cycle
void update_pwm_duty_cycle(unsigned int adc_value) {
    duty_cycle = (adc_value * 100) / 1023;         // Map ADC value to 0-100%
    temp = ((unsigned long)PWMMR0 * duty_cycle) / 100; // Use unsigned long
    PWMMR5 = (unsigned int)temp;                  // Update PWMMR5
    PWMLER = 1 << 5;                              // Latch enable for PWM5
}

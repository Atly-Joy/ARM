#include<lpc213x.h>

void adc_init() {
    PINSEL1 |= (1 << 24); // Select AD0.1 (P0.28) as ADC function
    AD0CR = (1 << 1) |    // Select AD0.1 channel
            (4 << 8) |    // ADC clock divider
            (1 << 21);    // Enable ADC
}

unsigned int read_adc() {
    AD0CR |= (1 << 24); // Start ADC conversion
    while (!(AD0GDR & (1 << 31))); // Wait for conversion to complete
    return (AD0GDR >> 6) & 0x3FF; // Extract 10-bit result
}

void pwm_init() {
    PINSEL0 = 1 << 3; // Set PWM3 on P0.1
    IO0DIR = ~0;
    PWMMR0 = 1000; // PWM period = 100 ms (100 * 1 ms)
    PWMMCR = 1 << 1; // Reset on PWMMR0
    PWMTCR = 2; // Counter reset
    PWMTCR = 1 | (1 << 3); // Counter enable and PWM enable
    PWMPR = 19999; // 1 ms timer period
    PWMTC = 0;
    PWMPC = 0;
    PWMPCR = 1 << 11; // Enable PWM3 output
}

void update_pwm_duty_cycle(unsigned int adc_value) {
    unsigned int duty_cycle = (adc_value * 100) / 1023; // Map ADC to 0-100%
    PWMMR3 = (PWMMR0 * duty_cycle) / 100; // Update PWMMR3
    PWMLER = 1 << 3; // Latch enable for PWM3
}

int main() {
    unsigned int adc_value;

    adc_init();
    pwm_init();

    while (1) {
        adc_value = read_adc(); // Read ADC value
        update_pwm_duty_cycle(adc_value); // Update PWM duty cycle
    }
}

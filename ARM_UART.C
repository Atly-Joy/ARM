#include <lpc213x.h>

// Function prototypes
void transmiter(char a);
char receiver();
void transmiter_string(const char *str);

int main() 
{
    char b;

    PINSEL0 = 0x00000005; // P0.0 as TXD0, P0.1 as RXD0
	U0LCR = 0x83;         // 8-bit data, 1 stop bit, no parity, enable DLAB
    U0DLM = 0x00;         // Set high byte of divisor to 0
    U0DLL = 130;           // pclk=20MHz
    U0LCR = 0x03;         // Disable DLAB, keep configuration as 8N1
	transmiter_string("BLAH BLAH BLAH.........\r\n");
    while (1) 
	{
        b = receiver();
        transmiter(b);
    }
}

char receiver() 
{
    while ((U0LSR & 0x01) == 0); // Wait for data to be available in the receiver buffer
    return U0RBR;         // Return the received character
}

void transmiter(char a) 
{
    
    while ((U0LSR & 0x20) == 0); // Wait until the transmit holding register is empty
    U0THR = a;           // Transmit the character
}
void transmiter_string(const char *str) 
{
    while (*str) 
	{
        transmiter(*str++); // Transmit each character
    }
}

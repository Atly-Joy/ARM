																	   /*
 * File:   AT_LCD1.c
 * Author: ASUS
 *
 * Created on September 24, 2024, 10:01 AM
 */


#include<lpc21xx.h>

void cmd(unsigned char a );
void data(unsigned char a );
void display(const char *p);
void _delay_ms(long j);
int main(void) 
{
    IODIR0=0XFFFFFFFF;
    cmd(0x01);
    cmd(0x0f);
    display("ATLY");
    while(1);
    return;
}


void cmd(unsigned char a )
{
	IOCLR0=0XFFFFFFFF;
    IOSET0=0x00040000;//RS=0,RW=0,E=1
    IOSET0=a;
    _delay_ms(1);
    IOCLR0=0x00040000;//RS=0,RW=0,E=0
    _delay_ms(3);
}
void data(unsigned char a )
{
	IOCLR0=0XFFFFFFFF;
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
    for(i=0;i<=j*10000;i++);
}
	

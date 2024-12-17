#include<LPC21XX.H>
int i;
unsigned char keypad(void);
void cmd(int a);
void data(char b);
void display(const char *p);
void delay(long int);
void main(void) {
PINSEL0=0x00000000;
PINSEL2=0x00000000;
IO1DIR=0xf0000;
IO0DIR=0xffffffff;
    cmd(0x38);   //2 lines and 5×7 matrix
    cmd(0x01);   //Clear display screen
    cmd(0x0f);   //Display on, cursor blinking
    while(1){
        unsigned char a;
        a=keypad();
        data(a);
        while((IO1PIN & 0XF00000 )!=0XF00000);
    }
    
    
}    
unsigned char keypad(void)
{
    while(1)								// 0000 0000 0010 0000 0000 0000 0000 0000 
    {										//			   2 	0	0	0		0	0
   	IO1CLR=0xf0000;
    IO1SET=0X10000;
    if((IO1PIN& 0X100000)==0)
    {
        return '0';
    }
    else if((IO1PIN& 0X200000)==0)
    {
        return '1';
    }
    else if((IO1PIN& 0X400000)==0)
    {
        return '2';
    }
    else if((IO1PIN& 0X800000)==0)
    {
        return '3';
    }
	IO1CLR=0xf0000 ;
	IO1SET=0X0D0000;
     if((IO1PIN& 0X100000)==0)
    {
         return '4';
    }
    else if((IO1PIN& 0X200000)==0)
    {
        return '5';
    }
    else if((IO1PIN& 0X400000)==0)
    {
        return '6';
    }
    else if((IO1PIN& 0X800000)==0)
    {
        return '7';
    }
IO1CLR=0xf0000;
IO1SET=0X0B0000; 
     if((IO1PIN& 0X100000)==0)
    {
         return '8';
    }
    else if((IO1PIN& 0X200000)==0)
    {
        return '9';
    }
    else if((IO1PIN& 0X400000)==0)
    {
        return 'A';
    }
    else if((IO1PIN& 0X800000)==0)
    {
        return 'B';
    }
IO1CLR=0xf0000;
IO1SET=0X070000;
    if((IO1PIN& 0X100000)==0)
    {
        return 'C';
    }
    else if((IO1PIN& 0X200000)==0)
    {
        return 'D';
    }
    else if((IO1PIN& 0X400000)==0)
    {
        return 'E';
    }
    else if((IO1PIN& 0X800000)==0)
    {
        return 'F';
    }
}
}
void cmd(int a)
{
   	IO0CLR=0x3ff;
   	IO0SET=a;
	IO0SET=0x200;
   	for(i=0;i<1000;i++)
   	IO0CLR=0x200;
}
void data(char b)
{
    IO0CLR=0x3ff;
	IO0SET=b;
	IO0SET=0x300;
	for(i=0;i<1000;i++)
	IO0CLR=0x200;
}
void display(const char *p){
    while(*p)
    { 
        data(*p);
        p++;
    }
}
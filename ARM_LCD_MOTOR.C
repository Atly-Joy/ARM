#include<lpc21xx.h>
void cmd(unsigned char a );
void data(unsigned char a );
void display(const char *p);
void _delay_ms(long j);
int count=0;
int main()
{
	IODIR0=0XFFFFFFFF;
    cmd(0x01);
    cmd(0x0f);
	//cmd(0x80);
	IODIR1=0x00000000;
	while(1)
	{
		display("PRESS THE BUTTON");
		if((IOPIN1&0X00010000)==0X00000000)
		{
		  count++;
		  while((IOPIN1&0X00010000)==0X00000000);
		}
		if(count==1)
		  {	
			  IOSET0=0X00000100;
			  cmd(0x80);
			  display("CLOCKWISE             ");	 
		  }
		else if(count==2)
		{
			 IOCLR0=0X00000100;
			 IOSET0=0X00000200;
			 cmd(0x80);
			 display("ANTI COLOCKWISE          ");
		}
		else if(count==3)
		{
			 IOCLR0=0X00000200;
			 IOSET0=0X00000000;
			 cmd(0x80);
			 display("STOPPED           ");
			 count=0;
		}
		
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
    for(i=0;i<=j*500;i++);
}

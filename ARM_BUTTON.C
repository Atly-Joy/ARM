#include<lpc21xx.h>
int count=0;
int main()
{
	IODIR0=0x0000000f;
	IODIR1=0x00000000;
	while(1)
	{
		if((IOPIN1&0X00010000)==0X00000000)
		{
		  count++;
		  while((IOPIN1&0X00010000)==0X00000000);
		}
		if(count==1)
		  {	
			  IOSET0=0X0000000f;	 
		  }
		else if(count==2)
		{
			 IOCLR0=0X0000000f;
			  count=0;
		}
		
	}
}
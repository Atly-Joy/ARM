#include<lpc21xx.h>
int i;
int main()
{
	IODIR0=0X00000080;//OR WE CAN TYPE fffffffff THAT WILL SET THEDIRECTION ALL THE PINS AS OUTPUT
	IODIR1=0X00800000;
	while(1)
	{
		IOSET0=0X00000080;//PIN HIGH
		IOSET1=0X00800000;
		for(i=0;i<60000;i++);
		IOCLR0=0X00000080;//TO CLEAR THE PIN WE HAVE TO PUT HIGH VALUE ON THE CORRESPONDING PIN
		IOCLR1=0X00800000;
		for(i=0;i<60000;i++);
	}
	return 0;
}
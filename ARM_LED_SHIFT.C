#include<lpc21xx.h>
int i;
int led_pattern = 0x00000001;
int main()
{
	PINSEL0=0X00000000;//// Set P0.0 to P0.7 as GPIO
	IODIR0=0X00000fff;//OR WE CAN TYPE fffffffff THAT WILL SET THEDIRECTION ALL THE PINS AS OUTPUT
	while(1)
	{
		IOSET0 = led_pattern;;//PIN HIGH
		for(i=0;i<10000;i++);
		IOCLR0=led_pattern;//TO CLEAR THE PIN WE HAVE TO PUT HIGH VALUE ON THE CORRESPONDING PIN
		for(i=0;i<10000;i++);
		led_pattern<<=1;
		if (led_pattern > 0x400) 
		{
            led_pattern = 0x00000001;
        }
	}
	return 0;
}
#include <lpc213x.h>

int main()
{
	int i,value;
	PINSEL1=0X80000;
	IODIR0=0X80000;
	IO0DIR = ( IO0DIR & 0xFFFFF0FF ); 
	while(1)
	{
		if ( !(IO0PIN & (1<<17)) )	//If switch for triangular wave is pressed
		{
			value = 0;
			while ( value != 1023 )
			{
				DACR = ( (1<<16) | (value<<6) );
				value++;
			}	
			while ( value != 0 )
			{
				DACR = ( (1<<16) | (value<<6) );
				value--;
			}
		}
		if ( !(IO0PIN & (1<<18)) )	//If switch for sawtooth wave is pressed
		{
		
			value = 0;
			while ( value != 1023 )
			{
				DACR = ( (1<<16) | (value<<6) );
				value++;
			}
		}
	}
}
#include<lpc213x.h>

void main()
{
  PINSEL0=1<<3;
  IO0DIR=~0;
  PWMMR0=10; //Pwm Timer  Period = 100ms ( 10 * 10mS)
  PWMMR3=5; // 50% Duty Cycle 50ms ON Time
  PWMTCR=2; // Counter ReseT
  PWMTCR=1|1<<3; // Counter Enable | PWM Enable
  PWMMCR=1<<1; // Reset on PWMMR0: the PWMTC will be reset if PWMMR0 matches it.
  PWMPR=199999; //1 mS Timer time period
  PWMTC=0;
  PWMPC=0; 
  PWMPCR=1<<11; //The PWM3 output enabled.
    while(1)
    {
    
    }
}
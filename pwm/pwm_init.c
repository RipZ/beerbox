#include <stdio.h>
#include <wiringPi.h>

int main (void)
{
    wiringPiSetup () ;
    pinMode (5, PWM_OUTPUT);
    pwmWrite (5, 0);

  return 0 ;
}

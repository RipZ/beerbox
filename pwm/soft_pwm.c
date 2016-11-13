#include <stdio.h>
#include <wiringPi.h>

#define	LED1	198
#define	LED2	199
#define	LED3	1
#define	LED4	67

const int pwmPin = 67;

int main (int argc, char *argv [])
{
    int prescaler;
    if (argc <2) return 0;
    prescaler = atoi(argv[1]);
    printf("argc = %d\n", argc);
    printf("prescaler = %d\n", prescaler);

    wiringPiSetup () ;
    softPwmCreate(pwmPin, 0, 100);
    softPwmWrite (pwmPin, prescaler);
    while (1)
          {
	    delay(10000);
          }

    return 0 ;
}

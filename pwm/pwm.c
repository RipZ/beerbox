/*
 * blink.c:
 *	Standard "blink" program in wiringPi. Blinks an LED connected
 *	to the first GPIO pin.
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <wiringPi.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.

#define	LED1	198
#define	LED2	199
#define	LED3	1
#define	LED4	67

#define wiringPiDebug 1

int main (int argc, char *argv [])
{
    int prescaler;

    prescaler = atoi(argv[1]);
    printf("prescaler = %d\n", prescaler);
    if (!prescaler) return 1;

    wiringPiSetup () ;
    pwmSetClock(8);
    pwmSetRange (1023) ;
    pinMode (5, PWM_OUTPUT);
//  pinMode (LED1, OUTPUT) ;
//  pinMode (LED2, OUTPUT) ;
//  pinMode (LED3, OUTPUT) ;
//  pinMode (LED4, OUTPUT) ;

//  pinMode (5, PWM_OUTPUT);

  pwmWrite (5, prescaler) ;

  return 0 ;
}

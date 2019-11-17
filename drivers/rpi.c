#ifndef LCD_RPI_DRIVER_C
#define LCD_RPI_DRIVER_C

#ifdef RPI

#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include "rpi.h"

void delayNanoseconds(unsigned int howLong) {
	struct timespec ts;
	ts.tv_nsec = howLong;

	nanosleep(&ts, &ts);
	
}

void __LCD_DRIVER_INIT() {
	wiringPiSetup();
	pinMode(0, OUTPUT);
}
void __LCD_DRIVER_WRITE_ZERO_SIG_UP() {
	digitalWrite(0, 1);
}

void __LCD_DRIVER_WRITE_ZERO_SIG_UP_AFTER() {
	delayNanoseconds(300);
}

void __LCD_DRIVER_WRITE_ZERO_SIG_DOWN() {
	digitalWrite(0, 0);
}

void __LCD_DRIVER_WRITE_ZERO_SIG_DOWN_AFTER() {
	delayNanoseconds(750);
}

void __LCD_DRIVER_WRITE_ONE_SIG_UP() {
	digitalWrite(0, 1);
}

void __LCD_DRIVER_WRITE_ONE_SIG_UP_AFTER() {
	delayNanoseconds(700);
}

void __LCD_DRIVER_WRITE_ONE_SIG_DOWN() {
	digitalWrite(0, 0);
}

void __LCD_DRIVER_WRITE_ONE_SIG_DOWN_AFTER() {
	delayNanoseconds(350);
}

void __LCD_DRIVER_WRITE_RESET() {
	digitalWrite(0, 0);
}

void __LCD_DRIVER_WRITE_RESET_AFTER() {
	usleep(51);
}

#endif
#endif /*LCD_RPI_DRIVER_C */
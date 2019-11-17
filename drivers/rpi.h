#ifndef __LCD_DRIVER_RPI_H
#define __LCD_DRIVER_RPI_H

#ifdef RPI
#include <wiringPi.h>


void __LCD_DRIVER_INIT() {
	wiringPiSetup();
	pinMode(0, OUTPUT);
}
void __LCD_DRIVER_WRITE_ZERO_SIG_UP() {
	digitalWrite(0, 1);
}

void __LCD_DRIVER_WRITE_ZERO_SIG_UP_AFTER() {
	//__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
}

void __LCD_DRIVER_WRITE_ZERO_SIG_DOWN() {
	digitalWrite(0, 0);
}

void __LCD_DRIVER_WRITE_ZERO_SIG_DOWN_AFTER() {
	//__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
}

void __LCD_DRIVER_WRITE_ONE_SIG_UP() {
	digitalWrite(0, 1);
}

void __LCD_DRIVER_WRITE_ONE_SIG_UP_AFTER() {
	//__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
}

void __LCD_DRIVER_WRITE_ONE_SIG_DOWN() {
	digitalWrite(0, 0);
}

void __LCD_DRIVER_WRITE_ONE_SIG_DOWN_AFTER() {
	//__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
}

void __LCD_DRIVER_WRITE_RESET() {
	digitalWrite(0, 0);
}
void __LCD_DRIVER_WRITE_RESET_AFTER();

#endif
#endif /* __LCD_DRIVER_RPI_H */
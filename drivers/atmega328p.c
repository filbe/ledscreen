#ifdef ATMEGA328P

#include "atmega328p.h"

void __LCD_DRIVER_WRITE_RESET_AFTER() {
	_delay_us(51);
}

#endif
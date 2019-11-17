#ifdef RPI

#include <time.h>
#include "rpi.h"

void __LCD_DRIVER_WRITE_RESET_AFTER() {
	micros(51);
}

#endif
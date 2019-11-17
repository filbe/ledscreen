#ifdef RPI

#include <time.h>
#include "rpi.h"

void __LCD_DRIVER_WRITE_RESET_AFTER() {
	nanosleep(51000);
}

#endif
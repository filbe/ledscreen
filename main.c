#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#include "ledscreen.h"

int main() {

	LCD_init();

	x_offset = 0;
	y_offset = 0;
	z_offset = 0;

	
	uint8_t frame = 0;

	while(1) {
		frame++;
		LCD_clearscreen_fade();

		// H
		LCD_drawline(3,0,0,3,255,0,0);
		LCD_drawline(7,0,4,3,255,0,0);
		LCD_drawline(2,1,5,2,255,0,0);

		// Y
		LCD_drawline(8,3,11,0,255,0,0);
		LCD_drawline(9,2,9,0,255,0,0);

		// V
		LCD_drawline(13,0,12,3,255,0,0);
		LCD_drawline(15,0,12,3,255,0,0);

		// Ä
		LCD_drawline(18,3,18,0,255,0,0);
		LCD_drawline(15,3,18,0,255,0,0);
		LCD_drawline(17,0,19,0,255,0,0);
		LCD_drawpixel(17,2,255,0,0);

		// Ä
		LCD_drawline(22,3,22,0,255,0,0);
		LCD_drawline(19,3,22,0,255,0,0);
		LCD_drawline(21,0,23,0,255,0,0);
		LCD_drawpixel(21,2,255,0,0);


		// J
		LCD_drawline(10,4,7,7,255,0,0);
		LCD_drawline(7,7,6,6,255,0,0);

		// O
		LCD_drawline(12,7,9,7,255,0,0);
		LCD_drawline(12,4,15,4,255,0,0);
		LCD_drawline(12,7,15,4,255,0,0);
		LCD_drawline(9,7,12,4,255,0,0);

		// U
		LCD_drawline(17,7,14,7,255,0,0);
		LCD_drawline(17,7,20,4,255,0,0);
		LCD_drawline(14,7,17,4,255,0,0);

		// L
		LCD_drawline(21,7,19,7,255,0,0);
		LCD_drawline(19,7,22,4,255,0,0);

		// U
		LCD_drawline(26,7,23,7,255,0,0);
		LCD_drawline(26,7,29,4,255,0,0);
		LCD_drawline(23,7,26,4,255,0,0);

		// A
		LCD_drawline(31,7,31,4,255,0,0);
		LCD_drawline(28,7,31,4,255,0,0);
		LCD_drawpixel(30,6,255,0,0);


		LCD_drawscreen();
		x_offset--;
		//y_offset++;
	}

	return 0;
}
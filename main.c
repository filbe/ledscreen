


#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#include "ledscreen.h"


/*
const uint8_t image_data[] PROGMEM = {
	255,255,255,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 255,255,255,255 , 1,1,1,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 1,1,1,255 , 255,255,255,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 1,1,1,255 , 0,0,0,255 , 1,1,1,255 , 255,255,255,255 , 75,205,9,255 , 75,205,9,255 , 255,255,255,255 , 1,1,1,255 , 0,0,0,255 , 1,1,1,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 0,1,0,255 , 1,1,1,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 69,193,8,255 , 69,193,8,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 1,1,1,255 , 0,1,0,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 1,1,1,255 , 1,1,1,255 , 81,220,12,255 , 255,255,255,255 , 255,255,255,255 , 57,189,0,255 , 82,197,24,255 , 82,197,24,255 , 57,189,0,255 , 255,255,255,255 , 255,255,255,255 , 81,220,12,255 , 1,1,1,255 , 1,1,1,255 , 255,255,255,255 , 255,255,255,255 , 0,0,0,255 , 255,255,255,255 , 58,189,0,255 , 70,193,8,255 , 70,193,8,255 , 70,193,8,255 , 70,193,8,255 , 70,193,8,255 , 70,193,8,255 , 70,193,8,255 , 70,193,8,255 , 58,189,0,255 , 255,255,255,255 , 0,0,0,255 , 255,255,255,255 , 1,1,1,255 , 1,1,1,255 , 255,255,255,255 , 255,255,255,255 , 70,193,8,255 , 57,189,0,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 57,189,0,255 , 70,193,8,255 , 255,255,255,255 , 255,255,255,255 , 1,1,1,255 , 1,1,1,255 , 0,0,0,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 59,190,0,255 , 255,255,255,255 , 254,255,254,255 , 255,255,255,255 , 255,255,255,255 , 254,255,254,255 , 255,255,255,255 , 59,190,0,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 0,0,0,255 , 0,0,0,255 , 255,255,255,255 , 254,255,254,255 , 255,255,255,255 , 59,190,0,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 59,190,0,255 , 255,255,255,255 , 254,255,254,255 , 255,255,255,255 , 0,0,0,255 , 0,0,0,255 , 255,255,255,255 , 255,255,255,255 , 57,189,0,255 , 70,193,8,255 , 255,255,255,255 , 254,255,254,255 , 255,255,255,255 , 255,255,255,255 , 254,255,254,255 , 255,255,255,255 , 70,193,8,255 , 57,189,0,255 , 255,255,255,255 , 255,255,255,255 , 0,0,0,255 , 0,0,0,255 , 75,205,9,255 , 69,192,8,255 , 87,210,25,255 , 87,210,25,255 , 62,201,0,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 62,201,0,255 , 87,210,25,255 , 87,210,25,255 , 69,192,8,255 , 75,205,9,255 , 0,0,0,255 , 0,0,0,255 , 91,222,26,255 , 92,223,26,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 92,223,26,255 , 91,222,26,255 , 0,0,0,255 , 0,1,0,255 , 1,1,1,255 , 0,0,0,255 , 0,0,0,255 , 255,255,255,255 , 255,255,255,255 , 0,0,0,255 , 255,255,255,255 , 255,255,255,255 , 0,0,0,255 , 255,255,255,255 , 255,255,255,255 , 0,0,0,255 , 0,0,0,255 , 1,1,1,255 , 0,1,0,255 , 255,255,255,255 , 0,0,0,255 , 1,1,1,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 0,0,0,255 , 255,255,255,255 , 255,255,255,255 , 0,0,0,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 1,1,1,255 , 0,0,0,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 0,0,0,255 , 255,255,255,255 , 254,254,254,255 , 254,254,254,255 , 255,255,255,255 , 254,254,254,255 , 254,254,254,255 , 255,255,255,255 , 254,254,254,255 , 254,254,254,255 , 255,255,255,255 , 0,0,0,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 255,255,255,255 , 1,1,1,255 , 1,1,1,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 1,1,1,255 , 1,1,1,255 , 255,255,255,255 , 255,255,255,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255 , 1,1,1,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 0,0,0,255 , 1,1,1,255 , 255,255,255,255 , 254,254,254,255 , 255,255,255,255
};
*/

int main() {

	LCD_init();

	x_offset = -1;
	y_offset = 0;
	z_offset = 0;

	
	uint8_t frame = 0;
	float a=0;
	while(1) {
		frame++;
		LCD_clearscreen();


		
		for (uint8_t line = 0; line < 10;line++) {
			uint8_t x1 = 16-line;
			uint8_t y1 = 8 - line;
			uint8_t x2 = 16 + line;
			uint8_t y2 = 8 + line;
			uint8_t r = sin(1.4*a+line*0.4)*127+127;
			uint8_t g = cos(1.7*a-line*0.4)*127+127;
			uint8_t b = sin(0.83*a+line*0.4)*127+127;

			LCD_drawline(x1,y1,x2,y1,r,g,b);
			LCD_drawline(x2,y2,x2,y1,r,g,b);
			LCD_drawline(x2,y2,x1,y2,r,g,b);
			LCD_drawline(x1,y2,x1,y1,r,g,b);


			LCD_drawline(x1+16,y1,x2+16,y1,r,g,b);
			LCD_drawline(x2+16,y2,x2+16,y1,r,g,b);
			LCD_drawline(x2+16,y2,x1+16,y2,r,g,b);
			LCD_drawline(x1+16,y2,x1+16,y1,r,g,b);
		}
		
		LCD_drawscreen();
		x_offset++;
		y_offset++;
		a+=0.2;
	}
	


	return 0;
}
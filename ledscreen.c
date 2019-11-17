/* Ledscreen driver library for microcontrollers
 * Author: Ville-Pekka Lahti (C) 2019
 * vp@wdr.fi
 * +358504686300
 * This project is tested with AtMega328P @ 16MHz
 */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "ledscreen.h"

#include "drivers/atmega328p.h"
//#include "drivers/rpi.h"



void LCD_init() {
	__LCD_DRIVER_INIT();
}
void _LCD_write_zero() {
	__LCD_DRIVER_WRITE_ZERO_SIG_UP();
	__LCD_DRIVER_WRITE_ZERO_SIG_UP_AFTER();
	__LCD_DRIVER_WRITE_ZERO_SIG_DOWN();
	__LCD_DRIVER_WRITE_ZERO_SIG_DOWN_AFTER();
}

void _LCD_write_one() {
	__LCD_DRIVER_WRITE_ONE_SIG_UP();
	__LCD_DRIVER_WRITE_ONE_SIG_UP_AFTER();
	__LCD_DRIVER_WRITE_ONE_SIG_DOWN();
	__LCD_DRIVER_WRITE_ONE_SIG_DOWN_AFTER();
}

void _LCD_write_reset() {
	__LCD_DRIVER_WRITE_RESET();
	__LCD_DRIVER_WRITE_RESET_AFTER();
}

void _LCD_send_component(uint8_t val) {
	val = val / 8;
	for (uint8_t i=0;i<8;i++) {
		if (val >> (7-i)) {
			_LCD_write_one();
		} else {
			_LCD_write_zero();
		}
	}
}

void _LCD_send_color(uint8_t r, uint8_t g, uint8_t b) {
	_LCD_send_component(g);
	_LCD_send_component(r);
	_LCD_send_component(b);
}

void LCD_drawpixel(uint8_t _x, uint8_t _y, uint8_t r, uint8_t g, uint8_t b) {
	uint8_t x=(_x + (int)(x_offset)) % SCREEN_W;
	uint8_t y=(_y + (int)(y_offset)) % SCREEN_H;

	#ifdef SECOND_PANEL_ON_BOTTOM
		if (y >= PANEL_H) {
			y-=PANEL_H;
			x+=PANEL_W;
		}
	#endif /* SECOND_SCREEN_ON_BOTTOM */

	#ifdef PANEL_LAYOUT_ZIGZAG
		if (x % 2) {
			y = 7-y;
		}
	#endif

	screen[x*PANEL_H+y][0] = r;
	screen[x*PANEL_H+y][1] = g;
	screen[x*PANEL_H+y][2] = b;
}

void LCD_draw_color_image(const uint8_t data[], uint16_t w, uint16_t h) {
	for (uint16_t y=0;y<h;y++) {
		for (uint16_t x=0;x<w;x++) {
			LCD_drawpixel(
				x,
				y,
				#ifdef AVR_PGMMEM
				pgm_read_byte(&data[(uint16_t)(y*w*3+x*3+0)]),
				pgm_read_byte(&data[(uint16_t)(y*w*3+x*3+1)]),
				pgm_read_byte(&data[(uint16_t)(y*w*3+x*3+2)])
				#else
				data[(uint16_t)(y*w*3+x*3+0)],
				data[(uint16_t)(y*w*3+x*3+1)],
				data[(uint16_t)(y*w*3+x*3+2)]
				#endif
			);
		}
	}
}

void LCD_drawscreen() {
	for (uint16_t i=0;i<SCREEN_SIZE;i++) {
		_LCD_send_color(screen[i][0],screen[i][1],screen[i][2]);
	}
	_LCD_write_reset();
}

void LCD_clearscreen() {
	for (uint16_t i=0;i<SCREEN_SIZE;i++) {
		screen[i][0] = 0;
		screen[i][1] = 0;
		screen[i][2] = 0;
	}
}


void LCD_drawline(int X0, int Y0, int X1, int Y1,uint8_t r, uint8_t g, uint8_t b)
{
	// calculate dx , dy
	float dx = X1 - X0;
	float dy = Y1 - Y0;

	// Depending upon absolute value of dx & dy
	// choose number of steps to put pixel as
	// steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy)
	float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	// calculate increment in x & y for each steps
	float Xinc = dx / (float) steps;
	float Yinc = dy / (float) steps;

	// Put pixel for each step
	float X = X0;
	float Y = Y0;
	for (int i = 0; i <= steps; i++)
	{
	    LCD_drawpixel(X,Y,r,g,b);
	    X += Xinc;
	    Y += Yinc;
	}
}

int c_3d_to_2d_x(int x, int y, float z) {
	return ((x) / (float)((float)z));
}

int c_3d_to_2d_y(int x, int y, float z) {
	return ((y) / (float)((float)z));
}

void LCD_draw_voxel_lineset(int8_t lineset[], uint8_t len, uint8_t r, uint8_t g, uint8_t b) {
	for (uint8_t i=0;i<len;i++) {
		int8_t x1 = c_3d_to_2d_x(lineset[i*6+0],lineset[i*6+1],lineset[i*6+2]);
		int8_t y1 = c_3d_to_2d_y(lineset[i*6+0],lineset[i*6+1],lineset[i*6+2]);
		int8_t x2 = c_3d_to_2d_x(lineset[i*6+3],lineset[i*6+4],lineset[i*6+5]);
		int8_t y2 = c_3d_to_2d_y(lineset[i*6+3],lineset[i*6+4],lineset[i*6+5]);
		LCD_drawline(x1,y1,x2,y2,r,g,b);
	}
}



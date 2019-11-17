#ifndef __LEDSCREEN_H_
#define __LEDSCREEN_H_



#define TR 							6
#define SECOND_SCREEN_ON_BOTTOM 	0

#define PANEL_W						32
#define PANEL_H						8
#define PANEL_LAYOUT_ZIGZAG 		1
#define SECOND_PANEL_ON_BOTTOM		0
#define SCREEN_W					PANEL_W
#define SCREEN_H					(PANEL_H * (1 + SECOND_PANEL_ON_BOTTOM))
#define SCREEN_SIZE 				(SCREEN_W * SCREEN_H)

float x_offset;
float y_offset;
float z_offset;


volatile uint8_t screen[SCREEN_SIZE][3];
void LCD_init();
void _LCD_write_zero();
void _LCD_write_one();
void _LCD_write_reset();
void _LCD_send_component(uint8_t val);
void _LCD_send_color(uint8_t r, uint8_t g, uint8_t b);
void LCD_drawpixel(uint8_t _x, uint8_t _y, uint8_t r, uint8_t g, uint8_t b);
void LCD_draw_color_image(const uint8_t data[], uint16_t w, uint16_t h);
void LCD_drawscreen();
void LCD_clearscreen();
void LCD_drawline(int X0, int Y0, int X1, int Y1,uint8_t r, uint8_t g, uint8_t b);
int c_3d_to_2d_x(int x, int y, float z);
int c_3d_to_2d_y(int x, int y, float z);
void LCD_draw_voxel_lineset(int8_t lineset[], uint8_t len, uint8_t r, uint8_t g, uint8_t b);




#endif
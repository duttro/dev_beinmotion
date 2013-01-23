#ifndef __SIMPLE_GRAPHICS_H__
#define __SIMPLE_GRAPHICS_H__

#define FONT_10PT_ROW 11
#define FONT_10PT_COLUMN 8

#define RGB16(r,g,b) ((((r&0xf8)<<8)|((g&0xfc)<<3)|(b>>3)))

void LCD_init(int);

void LCD_Draw_image(int Hstart, int Vstart,unsigned char no);

int LCD_print_string(int horiz_offset, int vert_offset, int color, char *font, char string[]);

int LCD_print_char (int horiz_offset, int vert_offset, int color, char character, char *font);

void LCD_draw_line(int horiz_start, int vert_start, int horiz_end, int vert_end, int width, int color );

void LCD_set_pixel(int horiz, int vert, unsigned int color);

unsigned short LCD_get_pixel(int horiz, int vert );

void LCD_draw_circle(int Hcenter, int Vcenter, int radius, int color, char fill );

int LCD_draw_round_corner_box ( int horiz_start, int vert_start, int horiz_end, int vert_end,
                                int radius, int color, int fill);

int LCD_draw_box (int horiz_start, int vert_start, int horiz_end, int vert_end, int color, int fill);

void LCD_paint_block (int Hstart, int Vstart, int Hend, int Vend, int color );

void LCD_draw_horiz_line (short Hstart, short Hend, int V, int color);

void LCD_draw_horiz_line (short Hstart, short Hend, int V, int color);

void LCD_draw_sloped_line( unsigned short horiz_start,
                           unsigned short vert_start,
                           unsigned short horiz_end,
                           unsigned short vert_end,
                           unsigned short width,
                           int color
                           );
#endif //__SIMPLE_GRAPHICS_H__

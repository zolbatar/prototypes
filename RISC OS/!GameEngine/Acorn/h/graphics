#ifndef H_GRAPHICS
#define H_GRAPHICS
#include <stdbool.h>
#include "types.h"

#define min2(a, b) ((a) < (b) ? (a) : (b))
#define min3(a, b, c) (min2(min2((a), (b)), (c)))
#define max2(a, b) ((a) > (b) ? (a) : (b))
#define max3(a, b, c) (max2(max2((a), (b)), (c)))

extern int screen_width;
extern int screen_height;
extern int x_origin;
extern int y_origin;

typedef struct {
	int x;
	int y;
} point_2d;

void graphics_setup();
void graphics_end();
void end_frame();
void clear_screen(UINT colour);
void set_clip(int x1, int y1, int x2, int y2);
void draw_horz_line(int x1, int x2, int y, UINT colour);
void draw_box(int x1, int y1, int x2, int y2, UINT colour);
void plot_pixel(int x, int y, UINT colour);
void draw_line(int x1, int y1, int x2, int y2, UINT colour);
void draw_polygon(int coords[], int size, UINT colour);
void fast_draw_triangle(bool gouraud, const point_2d *v0, const point_2d *v1, const point_2d *v2, UINT colour1, UINT colour2, UINT colour3);

#endif
#include "graphics.h"
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "types.h"

int screen_width;
int screen_height;
int x_origin;
int y_origin;
int size;
int size16m;

// Fast line lookup
int *line_address;
int *line_address_16m;

// Clipping
int minX;
int maxX;
int minY;
int maxY;

// Framebuffer
char *fbp = 0;

// Store the min and max X co-ords to draw horizontal lines on polygon, this is
// INEFFICIENT!!!
int *poly_min_x;
int *poly_max_x;

void end_frame() {}

void graphics_setup() {

    // Open the file for reading and writing
    int fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    struct fb_fix_screeninfo finfo;
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    struct fb_var_screeninfo vinfo;
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    // Setup mode sized stuff
    screen_width = vinfo.xres;
    screen_height = vinfo.yres;
    x_origin = screen_width / 2;
    y_origin = screen_height / 2;
    size = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    minX = 0;
    maxX = screen_width - 1;
    minY = 0;
    maxY = screen_height - 1;
    poly_min_x = malloc(sizeof(int) * screen_height);
    poly_max_x = malloc(sizeof(int) * screen_height);

    // Map the device to memory
    printf("Screen: %d x %d\n", screen_width, screen_height);
    fbp = (char *)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    // Fast lookup of line addresses
    line_address = malloc(sizeof(int) * screen_height);
    line_address_16m = malloc(sizeof(int) * screen_height);
    for (int i = 0; i < screen_height; i++) {
        line_address[i] = i * screen_width;
        line_address_16m[i] = (i * screen_width) << 2;
    }

    clear_screen(0);
}

void graphics_end() {}

UINT *get_bank_address() { return 0; }

void clear_screen(UINT colour) {
    UINT *addr = get_bank_address();
    for (int i = 0; i < size16m; i++) {
        addr[i] = colour;
    }
}

void set_clip(int x1, int y1, int x2, int y2) {
    minX = x1;
    maxX = x2;
    minY = y1;
    maxY = y2;
}

void draw_horz_line(int x1, int x2, int y, UINT colour) {
    UINT *addr = get_bank_address();
    int offset = line_address[y] + x1;

    for (int x = x1; x < x2; x++) {
        addr[offset++] = colour;
    }
}

void draw_box(int x1, int y1, int x2, int y2, UINT colour) {
    for (int y = y1; y < y2; y++) {
        draw_horz_line(x1, x2, y, colour);
    }
}

void plot_pixel(int x, int y, UINT colour) {
    UINT *addr = get_bank_address();
    int offset = line_address[y] + x;
    addr[offset] = colour;
}

void draw_line_raw(int x1, int y1, int x2, int y2, UINT colour) {
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (true) {
        plot_pixel(x1, y1, colour);
        if (x1 == x2 && y1 == y2) return;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y1 += sy;
        }
    }
}

typedef int OutCode;

const int INSIDE = 0;  // 0000
const int LEFT = 1;    // 0001
const int RIGHT = 2;   // 0010
const int BOTTOM = 4;  // 0100
const int TOP = 8;     // 1000

// Compute the bit code for a point (x, y) using the clip rectangle
// bounded diagonally by (minX, minY), and (maxX, maxY)

// ASSUME THAT maxX, minX, maxY and minY are global constants.

OutCode ComputeOutCode(int x, int y) {
    OutCode code;

    code = INSIDE;  // initialised as being inside of [[clip window]]

    if (x < minX)  // to the left of clip window
        code |= LEFT;
    else if (x > maxX)  // to the right of clip window
        code |= RIGHT;
    if (y < minY)  // below the clip window
        code |= BOTTOM;
    else if (y > maxY)  // above the clip window
        code |= TOP;

    return code;
}

// Cohen�Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with
// diagonal from (minX, minY) to (maxX, maxY).
void draw_line(int x0, int y0, int x1, int y1, UINT colour) {
    // compute outcodes for P0, P1, and whatever point lies outside the clip
    // rectangle
    OutCode outcode0 = ComputeOutCode(x0, y0);
    OutCode outcode1 = ComputeOutCode(x1, y1);
    bool accept = false;

    while (true) {
        if (!(outcode0 | outcode1)) {
            // bitwise OR is 0: both points inside window; trivially accept and
            // exit loop
            accept = true;
            break;
        } else if (outcode0 & outcode1) {
            // bitwise AND is not 0: both points share an outside zone (LEFT,
            // RIGHT, TOP, or BOTTOM), so both must be outside window; exit loop
            // (accept is false)
            break;
        } else {
            // failed both tests, so calculate the line segment to clip
            // from an outside point to an intersection with clip edge
            int x, y;

            // At least one endpoint is outside the clip rectangle; pick it.
            OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

            // Now find the intersection point;
            // use formulas:
            //   slope = (y1 - y0) / (x1 - x0)
            //   x = x0 + (1 / slope) * (ym - y0), where ym is minY or maxY
            //   y = y0 + slope * (xm - x0), where xm is minX or maxX
            // No need to worry about divide-by-zero because, in each case, the
            // outcode bit being tested guarantees the denominator is non-zero
            if (outcodeOut & TOP) {  // point is above the clip window
                x = x0 + (x1 - x0) * (maxY - y0) / (y1 - y0);
                y = maxY;
            } else if (outcodeOut & BOTTOM) {  // point is below the clip window
                x = x0 + (x1 - x0) * (minY - y0) / (y1 - y0);
                y = minY;
            } else if (outcodeOut & RIGHT) {  // point is to the right of clip window
                y = y0 + (y1 - y0) * (maxX - x0) / (x1 - x0);
                x = maxX;
            } else if (outcodeOut & LEFT) {  // point is to the left of clip window
                y = y0 + (y1 - y0) * (minX - x0) / (x1 - x0);
                x = minX;
            } else {
                // Unneeded, to avoid compiler warnings
                x = 0;
                y = 0;
            }

            // Now we move outside point to intersection point to clip
            // and get ready for next pass.
            if (outcodeOut == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = ComputeOutCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = ComputeOutCode(x1, y1);
            }
        }
    }

    if (accept) {
        draw_line_raw(x0, y0, x1, y1, colour);
    }
}

void draw_polygon_line(int x1, int y1, int x2, int y2, int pminY, int pmaxY) {
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (true) {
        if (y1 >= pminY && y1 <= pmaxY) {
            int yrel = y1 - pminY;
            if (x1 < poly_min_x[yrel]) poly_min_x[yrel] = x1;
            if (x1 > poly_max_x[yrel]) poly_max_x[yrel] = x1;
        }
        if (x1 == x2 && y1 == y2) return;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_polygon(int coords[], int len, UINT colour) {
    // Get Y limits
    int pminY = screen_height;
    int pmaxY = 0;
    int index = 1;
    for (int i = 0; i < len; i++) {
        if (coords[index] < pminY) pminY = coords[index];
        if (coords[index] > pmaxY) pmaxY = coords[index];
        index += 2;
    }
    if (pminY < minY) pminY = minY;
    if (pmaxY > maxY) pmaxY = maxY;

    // Work out total height
    int heightPoly = pmaxY - pminY;
    for (int i = 0; i <= heightPoly; i++) {
        poly_min_x[i] = maxX;
        poly_max_x[i] = -1;
    }

    // Render each line in turn, saving the min and max X
    index = 0;
    for (int i = 0; i < len - 1; i++) {
        draw_polygon_line(coords[index], coords[index + 1], coords[index + 2], coords[index + 3], pminY, pmaxY);
        index += 2;
    }
    draw_polygon_line(coords[index], coords[index + 1], coords[0], coords[1], pminY, pmaxY);

    for (int i = 0; i <= heightPoly; i++) {
        if (poly_min_x[i] != maxX && poly_max_x[i] != -1) {
            draw_horz_line(poly_min_x[i], poly_max_x[i], minY + pminY + i, colour);
        }
    }
}

int orient2d(const point_2d *a, const point_2d *b, const point_2d *c) { return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x); }

void fast_draw_triangle(bool gouraud, const point_2d *v0, const point_2d *v1, const point_2d *v2, UINT colour1, UINT colour2, UINT colour3) {
    // Bounding box
    int minXP = min3(v0->x, v1->x, v2->x);
    int minYP = min3(v0->y, v1->y, v2->y);
    int maxXP = max3(v0->x, v1->x, v2->x);
    int maxYP = max3(v0->y, v1->y, v2->y);

    // Zero size?
    if (minXP == maxXP || minYP == maxYP) {
        return;
    }

    // Clip to bounds
    minXP = max2(minXP, minX);
    minYP = max2(minYP, minY);
    maxXP = min2(maxXP, maxX);
    maxYP = min2(maxYP, maxY);

    // Triangle setup
    int A01 = v0->y - v1->y, B01 = v1->x - v0->x;
    int A12 = v1->y - v2->y, B12 = v2->x - v1->x;
    int A20 = v2->y - v0->y, B20 = v0->x - v2->x;

    // Barycentric coordinates at minX/minY corner
    point_2d p = {minXP, minYP};
    int w0_row = orient2d(v1, v2, &p);
    int w1_row = orient2d(v2, v0, &p);
    int w2_row = orient2d(v0, v1, &p);

    // Non gouraud? Merge colours
    int r, g, b;
    UINT col;
    if (!gouraud) {
        r = ((colour1 & 0xFF) * 0.33) + ((colour2 & 0xFF) * 0.33) + ((colour3 & 0xFF) * 0.33);
        b = (((colour1 & 0xFF00) >> 8) * 0.33) + (((colour2 & 0xFF00) >> 8) * 0.33) + (((colour3 & 0xFF00) >> 8) * 0.33);
        g = (((colour1 & 0xFF0000) >> 16) * 0.33) + (((colour2 & 0xFF0000) >> 16) * 0.33) + (((colour3 & 0xFF0000) >> 16) * 0.33);
        col = (b << 16) + (g << 8) + r;
    }

    // Rasterise
    for (p.y = minYP; p.y <= maxYP; p.y++) {
        float sum = w0_row + w1_row + w2_row;

        // Barycentric coordinates at start of row
        int w0 = w0_row;
        int w1 = w1_row;
        int w2 = w2_row;

        for (p.x = minXP; p.x <= maxXP; p.x++) {
            bool test = (w0 | w1 | w2) >= 0;
            if (test) {
                if (gouraud) {
                    float frac1 = w0 / sum;
                    float frac2 = w1 / sum;
                    float frac3 = w2 / sum;
                    int r = ((colour1 & 0xFF) * frac1) + ((colour2 & 0xFF) * frac2) + ((colour3 & 0xFF) * frac3);
                    int b = (((colour1 & 0xFF00) >> 8) * frac1) + (((colour2 & 0xFF00) >> 8) * frac2) + (((colour3 & 0xFF00) >> 8) * frac3);
                    int g = (((colour1 & 0xFF0000) >> 16) * frac1) + (((colour2 & 0xFF0000) >> 16) * frac2) + (((colour3 & 0xFF0000) >> 16) * frac3);
                    UINT col = (b << 16) + (g << 8) + r;
                    //					col = 0x00FF0000;
                    plot_pixel(p.x, p.y, col);
                } else {
                    plot_pixel(p.x, p.y, col);
                }
            }

            // One step to the right
            w0 += A12;
            w1 += A20;
            w2 += A01;
        }

        // One row step
        w0_row += B12;
        w1_row += B20;
        w2_row += B01;
    }
}
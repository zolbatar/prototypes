#ifndef H_ENGINE
#define H_ENGINE
#include <stdbool.h>
#include "types.h"

extern bool wireframe;
extern bool gouraud;

typedef struct {
	float lx, ly, lz;	// Local
	float wx, wy, wz;	// World
	int sx, sy;		// Screen
	bool render;
} vertex_type;

typedef struct {
	int v1, v2, v3;
	float nx, ny, nz;	// Normal
	UINT colour;
} face_type;

typedef struct {
	int number_of_vertices;
	int number_of_faces;
	vertex_type *vertex;
	face_type *face;
} shape_type;

void inittrans();
void calcvisible(shape_type *shape, float tx, float ty, float tz, float horizon);
void scale(float sf);
void translate(float xt, float yt, float zt);
void rotate(float ax, float ay, float az);
void transform(shape_type *shape);
void project(shape_type *shape, int distance);
void draw_shape(shape_type *shape);
void calc_normal(shape_type *shape, face_type *face);
float calc_dot_product(float x1, float y1, float z1, float x2, float y2, float z2);

#endif

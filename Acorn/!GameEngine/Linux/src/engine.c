#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graphics.h"
#include "engine.h"

bool wireframe = false;
bool gouraud = false;

// Various matrices for transformations
float matrix[4][4];

void matmult(float result[4][4], float mat1[4][4], float mat2[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				result[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}

void matcopy(float dest[4][4], float source[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			dest[i][j] = source[i][j];
		}
	}
}

void inittrans() {
	// Init master transformation matrix to the identity matrix

	matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 0; matrix[0][3] = 0;
	matrix[1][0] = 0; matrix[1][1] = 1; matrix[1][2] = 0; matrix[1][3] = 0;
	matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 1; matrix[2][3] = 0;
	matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1;
}

void scale(float sf) {
	float smat[4][4];
	float mat[4][4];

	// Init scaling matrix
	smat[0][0] = sf; smat[0][1] = 0;  smat[0][2] = 0;  smat[0][3] = 0;
	smat[1][0] = 0;  smat[1][1] = sf; smat[1][2] = 0;  smat[1][3] = 0;
	smat[2][0] = 0;  smat[2][1] = 0;  smat[2][2] = sf; smat[2][3] = 0;
	smat[3][0] = 0;  smat[3][1] = 0;  smat[3][2] = 0;  smat[3][3] = 1;

	// Concatenate with master matrix
	matmult(mat, smat, matrix);
	matcopy(matrix, mat);
}

void translate(float xt, float yt, float zt) {
	float tmat[4][4];
	float mat[4][4];

	// Create a translation matrix that will translate an object from screen origin

	// Init translation matrix
	tmat[0][0] = 1;  tmat[0][1] = 0;  tmat[0][2] = 0;   tmat[0][3] = 0;
	tmat[1][0] = 0;  tmat[1][1] = 1;  tmat[1][2] = 0;   tmat[1][3] = 0;
	tmat[2][0] = 0;  tmat[2][1] = 0;  tmat[2][2] = 1;   tmat[2][3] = 0;
	tmat[3][0] = xt; tmat[3][1] = yt; tmat[3][2] = zt;  tmat[3][3] = 1;

	// Concatenate with master matrix
	matmult(mat, matrix, tmat);
	matcopy(matrix, mat);
}

void rotate(float ax, float ay, float az) {
	float xmat[4][4];
	float ymat[4][4];
	float zmat[4][4];
	float mat1[4][4];
	float mat2[4][4];

	// Create three rotations matrices that will rotate an object

	// Init rotate X matrix
	xmat[0][0] = 1; xmat[0][1] = 0;        xmat[0][2] = 0;       xmat[0][3] = 0;
	xmat[1][0] = 0; xmat[1][1] = cos(ax);  xmat[1][2] = sin(ax); xmat[1][3] = 0;
	xmat[2][0] = 0; xmat[2][1] = -sin(ax); xmat[2][2] = cos(ax); xmat[2][3] = 0;
	xmat[3][0] = 0; xmat[3][1] = 0;        xmat[3][2] = 0;       xmat[3][3] = 1;
	matmult(mat1, xmat, matrix);

	// Init rotate Y matrix
	ymat[0][0] = cos(ay); ymat[0][1] = 0; ymat[0][2] = -sin(ay); ymat[0][3] = 0;
	ymat[1][0] = 0;       ymat[1][1] = 1; ymat[1][2] = 0;        ymat[1][3] = 0;
	ymat[2][0] = sin(ay); ymat[2][1] = 0; ymat[2][2] = cos(ay);  ymat[2][3] = 0;
	ymat[3][0] = 0;       ymat[3][1] = 0; ymat[3][2] = 0;        ymat[3][3] = 1;
	matmult(mat2, ymat, mat1);

	// Init rotate Z matrix
	zmat[0][0] = cos(az);  zmat[0][1] = sin(az); zmat[0][2] = 0; zmat[0][3] = 0;
	zmat[1][0] = -sin(az); zmat[1][1] = cos(az); zmat[1][2] = 0; zmat[1][3] = 0;
	zmat[2][0] = 0;        zmat[2][1] = 0;       zmat[2][2] = 1; zmat[2][3] = 0;
	zmat[3][0] = 0;        zmat[3][1] = 0;       zmat[3][2] = 0; zmat[3][3] = 1;
	matmult(matrix, zmat, mat2);
}

void transform(shape_type *shape) {
	for(int v = 0; v < (*shape).number_of_vertices; v++) {
		vertex_type *vptr = &(*shape).vertex[v];
		if (vptr->render) {
			vptr->wx = vptr->lx * matrix[0][0] + vptr->ly * matrix[1][0] + vptr->lz * matrix[2][0] + matrix[3][0];
			vptr->wy = vptr->lx * matrix[0][1] + vptr->ly * matrix[1][1] + vptr->lz * matrix[2][1] + matrix[3][1];
			vptr->wz = vptr->lx * matrix[0][2] + vptr->ly * matrix[1][2] + vptr->lz * matrix[2][2] + matrix[3][2];
		}
	}
}

void project(shape_type *shape, int distance) {
	for (int v = 0; v < (*shape).number_of_vertices; v++) {
		vertex_type *vptr = &(*shape).vertex[v];
		if (vptr->render) {
			float z = vptr->wz;
			if (z <= 0.0) z = 0.0001;
			vptr->sx = distance * vptr->wx / z;
			vptr->sy = distance * vptr->wy / z;
		}
	}
}

void calc_normal(shape_type *shape, face_type *face) {
	float x1 = shape->vertex[face->v1].wx;
	float x2 = shape->vertex[face->v2].wx;
	float x3 = shape->vertex[face->v3].wx;
	float y1 = shape->vertex[face->v1].wy;
	float y2 = shape->vertex[face->v2].wy;
	float y3 = shape->vertex[face->v3].wy;
	float z1 = shape->vertex[face->v1].wz;
	float z2 = shape->vertex[face->v2].wz;
	float z3 = shape->vertex[face->v3].wz;

	// Generate normal
	face->nx = (y2 - y1) * (z3 - z1) - (z2 - z1) * (y3 - y1);
	face->ny = (z2 - z1) * (x3 - x1) - (x2 - x1) * (z3 - z1);
	face->nz = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);

	// Normalise, if != 0
	float l = sqrt(face->nx * face->nx + face->ny * face->ny + face->nz * face->nz);
	face->nx /= l;
	face->ny /= l;
	face->nz /= l;
}

float calc_dot_product(float x1, float y1, float z1, float x2, float y2, float z2) {
	return (x1 * x2) + (y1 * y2) + (z1 * z2);
}

float shoelace(shape_type *shape, face_type *face) {
	int x1 = shape->vertex[face->v1].sx;
	int x2 = shape->vertex[face->v2].sx;
	int x3 = shape->vertex[face->v3].sx;
	int y1 = shape->vertex[face->v1].sy;
	int y2 = shape->vertex[face->v2].sy;
	int y3 = shape->vertex[face->v3].sy;

	return 	((x1 * y2) - (x2 * y1)) +
			((x2 * y3) - (x3 * y2)) +
			((x3 * y1) - (x1 * y3));
}

void calcvisible(shape_type *shape, float tx, float ty, float tz, float horizon) {
	for(int v = 0; v < (*shape).number_of_vertices; v++) {
		vertex_type *vptr = &(*shape).vertex[v];

		// Adjust local co-ordinate by translation co-ordinate
		float ez = vptr->lz + tz;

		// Check z co-ord first
		if (ez <= 5 || ez > horizon) {
			vptr->render = false;
		} else {
			vptr->render = true;
		}
	}
}

void draw_shape(shape_type *shape) {
	if (wireframe) {
		for (int i = 0; i < shape->number_of_faces; i++) {
			face_type *face = &shape->face[i];
			vertex_type *v1 = &shape->vertex[face->v1];
			vertex_type *v2 = &shape->vertex[face->v2];
			vertex_type *v3 = &shape->vertex[face->v3];

			// Render?
			if (!v1->render || !v2->render || !v3->render)
				continue;

			draw_line(v1->sx + x_origin, v1->sy + y_origin, v2->sx + x_origin, v2->sy + y_origin, face->colour);
			draw_line(v1->sx + x_origin, v1->sy + y_origin, v3->sx + x_origin, v3->sy + y_origin, face->colour);
			draw_line(v2->sx + x_origin, v2->sy + y_origin, v3->sx + x_origin, v3->sy + y_origin, face->colour);
		}
 	} else {
		for (int i = 0; i < shape->number_of_faces; i++) {
			face_type *face = &shape->face[i];
			vertex_type *v1 = &shape->vertex[face->v1];
			vertex_type *v2 = &shape->vertex[face->v2];
			vertex_type *v3 = &shape->vertex[face->v3];

			// Render?
			if (!v1->render || !v2->render || !v3->render)
				continue;

			point_2d v0p = { v1->sx + x_origin, v1->sy + y_origin };
			point_2d v1p = { v2->sx + x_origin, v2->sy + y_origin };
			point_2d v2p = { v3->sx + x_origin, v3->sy + y_origin };
			fast_draw_triangle(gouraud, &v0p, &v1p, &v2p, face->colour, face->colour, face->colour);

			// Show normal
//			int x = (v0p.x + v1p.x + v2p.x) / 3;
//			int y = (v0p.y + v1p.y + v2p.y) / 3;
//			draw_line(x, y, x, y, 0x00FF0000);
		}
	}
}
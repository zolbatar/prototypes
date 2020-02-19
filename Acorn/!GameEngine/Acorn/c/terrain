#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graphics.h"
#include "engine.h"
#include "palette.h"
#include "perlin.h"
#include "terrain.h"

// This is the actual hills/mountains, which moves in a parallex way
vertex_type terrain_vertices[TERRAIN_VERTEX_COUNT];
face_type terrain_faces[TERRAIN_FACE_COUNT];
shape_type terrain_shape = {
	TERRAIN_VERTEX_COUNT,
	TERRAIN_FACE_COUNT,
	terrain_vertices,
	terrain_faces,
};

UINT get_colour(float dp, int y) {
	UINT colour = 0;
	if (dp >= 0) {
		if (y < -80.0) { 		// Snow
			colour = mix_colour(0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, dp);
		} else {
			colour = mix_colour(0x20, 0x20, 0x20, 0xFF, 0xFF, 0xFF, dp);
		}
	} else {
		if (y < -80.0) { 			// Snow
			colour = 0x00606060;
		} else {
			colour = 0x00202020;
		}
	}
	return colour;
}

void generate_terrain() {

	// Create "shape" of terrain, mountains each side here
	float y_adjust[TERRAIN_SIZE_WIDTH];
	for (int i = 0; i < TERRAIN_SIZE_WIDTH / 2; i++) {
		if (i <= 25) {
			y_adjust[i] = (30 - i) * (30 - i);

//			if (i == 0) y_adjust[i] *= 0.75;
//			if (i == 1) y_adjust[i] *= 0.85;
//			if (i == 2) y_adjust[i] *= 0.95;

			y_adjust[99 - i] =  y_adjust[i];
		} else {
			y_adjust[i] = 20;
			y_adjust[99 - i] = 20;
		}
		y_adjust[i] /= 2500;
		y_adjust[99 - i] /= 2500;
	}

	// Create vertices
	float half_width = TERRAIN_SIZE_WIDTH * TERRAIN_SEGMENT / 2;
	float half_height = TERRAIN_SIZE_HEIGHT * TERRAIN_SEGMENT / 2;
	int i = 0;
	for(int y = 0; y < TERRAIN_SIZE_HEIGHT; y++) {
		for(int x = 0; x < TERRAIN_SIZE_WIDTH; x++) {
			// Perlin value
			float v = -perlin2d(x, y, 0.25, 1) * y_adjust[x] * TERRAIN_SCALE;

			vertex_type *vt = &terrain_vertices[i++];
			vt->render = true;
			vt->lx = (x * TERRAIN_SEGMENT) - half_width;
			vt->lz = (y * TERRAIN_SEGMENT) - half_height;
			vt->ly = v;
		}
	}
	terrain_shape.number_of_vertices = i;

	// Create polygons
	i = 0;
	for(int y = 0; y < TERRAIN_SIZE_HEIGHT - 1; y++) {
		for(int x = 0; x < TERRAIN_SIZE_WIDTH - 1; x++) {

			bool vertex1 = terrain_vertices[(y * TERRAIN_SIZE_WIDTH) + x].ly != 0.0;
			bool vertex2 = terrain_vertices[(y * TERRAIN_SIZE_WIDTH) + x + 1].ly != 0.0;
			bool vertex3 = terrain_vertices[((y + 1) * TERRAIN_SIZE_WIDTH) + x].ly != 0.0;
			bool vertex4 = terrain_vertices[((y + 1) * TERRAIN_SIZE_WIDTH) + x + 1].ly != 0.0;

			if (vertex4 && vertex3 && vertex1) {
				face_type *ft = &terrain_faces[i++];
				ft->v1 = (y * TERRAIN_SIZE_WIDTH) + x + 1;		// V2
	 			ft->v2 = ft->v1 - 1;							// V1
				ft->v3 = ft->v2 + TERRAIN_SIZE_WIDTH;			// V3
			}

			if (vertex2 && vertex4 && vertex3) {
				face_type *ft = &terrain_faces[i++];
				ft->v1 = ((y + 1) * TERRAIN_SIZE_WIDTH) + x;	// V3
				ft->v2 = ft->v1 + 1;							// V4
				ft->v3 = ft->v2 - TERRAIN_SIZE_WIDTH;			// V2
			}
		}
	}
	terrain_shape.number_of_faces = i;

	// Work out normals to colour the mountains
	inittrans();
	translate(0, 0, 0);
	transform(&terrain_shape);
	for (int i = 0; i < terrain_shape.number_of_faces; i += 2) {
		face_type *face = &terrain_shape.face[i];
		calc_normal(&terrain_shape, face);
		float dp = calc_dot_product(face->nx, face->ny, face->nz, 0, 0.3, 0.7);

		// Work out height
		float y1 = terrain_vertices[face->v1].ly;
		float y2 = terrain_vertices[face->v2].ly;
		float y3 = terrain_vertices[face->v3].ly;
		float avg = (y1 + y2 + y3) / 3;

		// Set face colour
		face->colour = get_colour(dp, avg);

		// Set face of matching other triangle
		face = &terrain_shape.face[i + 1];
		face->colour = get_colour(dp, avg);
	}
}

void render_terrain(float cx, float cy, float cz) {
	inittrans();
	calcvisible(&terrain_shape, cx, cy, cz, 750.0);
	translate(cx, cy, cz);
	transform(&terrain_shape);
	project(&terrain_shape, 200);
	draw_shape(&terrain_shape);
}
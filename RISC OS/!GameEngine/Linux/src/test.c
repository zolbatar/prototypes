#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"
#include "palette.h"
#include "engine.h"
#include "test.h"

void line_test() {
	clear_screen(0);
	for (int xx = 0; xx < 5; xx++) {
		draw_horz_line(xx, (xx << 1) + 1, xx + 100, 255);
	}
//	end_frame();
}

void performance_test() {
	int width = screen_width - 1;
	int height = screen_height - 1;
	for (int i = 0; i < 1; i++) {
//		test_palette();
		clear_screen(0);
		set_clip(0, 0, width - 1, height);
		draw_box(0, 0, width - 1, height, 0x00101010);
		set_clip(10, 10, width - 10, height - 10);
/*		for (int xx = 0; xx < 150; xx++) {
			draw_horz_line(xx + 1, (xx << 1) + 1, xx, xx + 1);
		}
		for (int xx = 0; xx < 5000; xx++) {
			draw_line(rand() % width, rand() % height, rand() % height, rand() % height, rand() % 255);
		}*/

		for (int j = 0; j < 1000; j++) {
			point_2d v0 = { rand() % width, rand() % height };
			point_2d v1 = { rand() % width, rand() % height };
			point_2d v2 = { rand() % width, rand() % height };
			UINT colour1 = ((rand() % 255) << 16) + ((rand() % 255) << 8) + (rand() % 255);
			UINT colour2 = ((rand() % 255) << 16) + ((rand() % 255) << 8) + (rand() % 255);
			UINT colour3 = ((rand() % 255) << 16) + ((rand() % 255) << 8) + (rand() % 255);
//			fast_draw_triangle(&v0, &v1, &v2, colour1, colour2, colour3);

//			int coords[6] = { rand() % width, rand() % height, rand() % width, rand() % height, rand() % width, rand() % height };
//			draw_polygon(coords, 3, rand() % 255);
		}
//		int coords2[] = { 0, 0, width, 120, 50, height };
//		draw_polygon(coords2, 3, 10);

		point_2d v0 = { 0, 0 };
		point_2d v1 = { width, 120 };
		point_2d v2 = { 50, height };
//		point_2d v0 = { 50, 50 };
//		point_2d v1 = { 55, 55 };
//		point_2d v2 = { 50, 60 };
		fast_draw_triangle(true, &v0, &v1, &v2, 0xFF0000, 0x00FF00, 0x0000FF);

//		end_frame();
	}
}

void spinning_cube() {
	vertex_type cube_vertices[] = {
		-10,-10,10,	// 0
		0,0,0,
		0,0,
		true,
		10,-10,10,	// 1
		0,0,0,
		0,0,
		true,
		10,10,10,	// 2
		0,0,0,
		0,0,
		true,
		-10,10,10,	// 3
		0,0,0,
		0,0,
		true,
		-10,-10,-10,// 4
		0,0,0,
		0,0,
		true,
		10,-10,-10,	// 5
		0,0,0,
		0,0,
		true,
		10,10,-10,	// 6
		0,0,0,
		0,0,
		true,
		-10,10,-10,	// 7
		0,0,0,
		0,0,
		true,
	};

	face_type cube_faces[] = {
		4,5,7,1,
		0,0,0,
		7,5,6,1,
		0,0,0,
		6,5,1,2,
		0,0,0,
		6,1,2,2,
		0,0,0,
		0,4,3,3,
		0,0,0,
		4,7,3,3,
		0,0,0,
		1,0,3,4,
		0,0,0,
		1,3,2,4,
		0,0,0,
		4,0,1,5,
		0,0,0,
		4,1,5,5,
		0,0,0,
		3,7,6,6,
		0,0,0,
		6,2,3,6,
		0,0,0,
	};

	shape_type shape = {
		false,
		8,		// vertices
		12,		// faces
		cube_vertices,
		cube_faces,
	};

	for (int i = 0; i < 250; i++) {
		float r = (float)i / 100;
		clear_screen(0);
		inittrans();
		scale(5);
		rotate(r, r, r);
		translate(0, 0, 150);
		transform(&shape);
		project(&shape, 150);
		draw_shape(&shape);
		end_frame();
	}
}
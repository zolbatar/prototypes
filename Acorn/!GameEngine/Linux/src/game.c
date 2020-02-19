#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graphics.h"
#include "terrain.h"
#include "palette.h"
#include "keyboard.h"

void game_loop() {

	// Camera position
	float camera_x = 0.0, camera_y = 15.0, camera_z = TERRAIN_SIZE_HEIGHT * TERRAIN_SEGMENT / 2;

	float frac = 0.1 / (screen_height / 2);
	while(true) {
//		clear_screen(0);
//		set_clip(0, 0, screen_width - 1, screen_height - 1);

		// Shaded sky
/*		for (int i = 0; i < screen_height / 2; i++) {
			UINT colour = mix_colour(0x7, 0x0B, 0x34, 0xFF, 0xFF, 0xFF, i * frac);
			draw_horz_line(0, screen_width - 1,i, colour);
		}*/

		// Shaded ground
/*		for (int i = 0 ; i < (screen_height / 2); i++) {
			UINT colour = mix_colour(0x60, 0x60, 0x60, 0xFF, 0xFF, 0xFF, (screen_height / 2 - (i * 2)) * frac);
			draw_horz_line_16m(0, screen_width - 1, (screen_height / 2) + i, colour);
		}*/

		render_terrain(camera_x, camera_y, camera_z);

		// Keys
		BYTE res = check_for_key();
		switch (res) {
			case 0:
				break;
			default:
				printf("%d\n ", res);
				break;
			case KEY_ESCAPE:	// Escape = Quit
				return;
/*			case KEY_Q:			// Q = wireframe off
				wireframe = false;
				break;
			case KEY_W:			// W = wireframe on
				wireframe = true;
				break;
			case KEY_E:			// E = gouraud off
				gouraud = false;
				break;
			case KEY_R:			// R = gouraud on
				gouraud = true;
				break;

			case KEY_LEFT:		// Left = move left
				camera_x += 1.0;
				break;
			case KEY_RIGHT:		// Right = move right
				camera_x -= 1.0;
				break;
			case KEY_UP:		// Up, push into scene
				camera_z -= 1.0;
				break;
			case KEY_DOWN:		// Down, push out of scene
				camera_z += 1.0;
				break;
			case PAGE_UP:		// Page up = raise
				camera_y += 1.0;
				break;
			case PAGE_DOWN:		// Page down = lower
				camera_y -= 1.0;
				break;*/
		}

//		end_frame();
	}
}
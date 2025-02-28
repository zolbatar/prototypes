#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graphics.h"
#include "terrain.h"
#include "palette.h"
#include "engine.h"
#include "test.h"
#include "game.h"

void performance_test();
void spinning_cube();

clock_t t;

void time_start() {
	t = clock();
}

void time_end() {
	clock_t tt = clock() - t;
	printf("Took %d - %f seconds to execute \n", (int)tt, ((float)tt) / CLOCKS_PER_SEC);
}

int main() {

	// Set things uo
	graphics_setup();
	keyboard_init();
//	generate_terrain();

	// Loop
	t = clock();
	time_start();
//	performance_test();
	game_loop();
//	spinning_cube();

	// Shutdown
	time_end();
//	end_frame();
//	graphics_end();
}
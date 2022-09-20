#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <imgui.h>
#include "../../ImGuiBindings/imgui_impl_sdl.h"
#include "../../ImGuiBindings/imgui_impl_opengl3.h"

class UI
{
 public:
	UI();
	~UI();
	void Loop();

 private:
	void _CreateWindow();
	void SetupDearImgui();
	void SetupOpenGL();
	void SetupFPS();

	std::string glsl_version;
	SDL_GLContext gl_context;
	float fps_values[64];
	size_t fps_offset = 0;
	size_t frame_count = 0;
	std::string fps_text = "0 FPS";
	std::chrono::steady_clock::time_point fps_clock;
	const float font_size = 14.0f;
	const bool fullscreen = false;
	float dpi_ratio;
	int desktop_screen_width, desktop_screen_height;
	SDL_Window* window;
	//ImFont *font;
};

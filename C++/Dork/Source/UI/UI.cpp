#include <iostream>
#include "UI.h"

UI::UI()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError() << std::endl;
	}

	float ddpi, hdpi, vdpi;
	if (SDL_GetDisplayDPI(0, &ddpi, &hdpi, &vdpi) != 0)
	{
		std::cout << "ERROR: Failed to obtain DPI information for display 0: \n" << SDL_GetError() << std::endl;
		exit(1);
	}
	dpi_ratio = ddpi / 72.0f;
	std::cout << "DPI ratio: " << dpi_ratio << std::endl;

	SDL_DisplayMode dm;
	if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
	{
		std::cout << "ERROR: SDL_GetDesktopDisplayMode failed: " << SDL_GetError() << std::endl;
		exit(1);
	}
	desktop_screen_width = dm.w;
	desktop_screen_height = dm.h;
	std::cout << "Desktop resolution: " << desktop_screen_width << "x" << desktop_screen_height << std::endl;
	_CreateWindow();
	SetupOpenGL();
	SetupDearImgui();
	SetupFPS();
}

UI::~UI()
{
	std::cout << "Shutting down SDL" << std::endl;
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void UI::SetupOpenGL()
{
	// Decide GL+GLSL versions
	std::cout << "Setting up OpenGL version" << std::endl;
#if defined(IMGUI_IMPL_OPENGL_ES2)
	TerminalOut("OpenGL", "GL ES 2.0 + GLSL 150");
	// GL ES 2.0 + GLSL 100
	glsl_version = "#version 100";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
	std::cout << "OpenGL:GL 3.2 Core + GLSL 330" << std::endl;
	// GL 3.2 Core + GLSL 150
	glsl_version = "#version 330";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	std::cout << "OpenGL:GL GL 3.0 + GLSL 130" << std::endl;
	// GL 3.0 + GLSL 130
	glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	// Create context in window
	gl_context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync
}

void UI::_CreateWindow()
{
	// Create window
	std::cout << "Creating SDL window\n";
	SDL_WindowFlags window_flags;
	if (fullscreen)
	{
		window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
		//window_flags = (SDL_WindowFlags) (SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI);
		window = SDL_CreateWindow("Daric",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			desktop_screen_width,
			desktop_screen_height,
			window_flags);
	}
	else
	{
#ifdef __x86_64__
		desktop_screen_width = 1920;
		desktop_screen_height = 1080;
#else
		desktop_screen_width = 1280;
		desktop_screen_height = 720;
#endif
		window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
		window = SDL_CreateWindow("Daric",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			desktop_screen_width,
			desktop_screen_height,
			window_flags);
	}
	if (window == nullptr)
	{
		std::cout << "ERROR: Window could not be created. SDL_Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
}

void UI::SetupDearImgui()
{
	// Setup Dear ImGui context
	std::cout << "Setting up Dear ImGui core" << std::endl;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.Fonts->Clear();
	io.Fonts->AddFontFromFileTTF("SourceCodePro-Regular.ttf", font_size * dpi_ratio);
	//font = io.Fonts->AddFontFromFileTTF("RobotoMono-Regular.ttf", font_size * dpi_ratio);
	io.FontGlobalScale /= dpi_ratio;
	io.Fonts->Build();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	std::cout << "Setting up Dear ImGui renderer" << std::endl;
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}

void UI::SetupFPS()
{
	// FPS stuff
	std::string fps_text = "0 FPS";
	for (auto i = 0; i < 64; i++)
	{
		fps_values[i] = 0.0f;
	}
}

void UI::Loop()
{
	fps_clock = std::chrono::steady_clock::now();
	bool done = false;
	bool window_output = true;
	bool demo_output = false;
	auto io = ImGui::GetIO();
	world.Reset();
	while (!done)
	{
		// Process SDL events like keyboard & mouse
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				done = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
				done = true;
		}

		glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		const ImGuiViewport* main_viewport = ImGui::GetMainViewport();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		// Full screen "window"
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::SetNextWindowPos(main_viewport->Pos);
		ImGui::SetNextWindowSize(main_viewport->Size);
		ImGui::Begin("Fullscreen", &window_output,
			ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoBackground);
		world.Render(main_viewport);
		ImGui::End();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();

		// FPS histogram
		ImGui::SetNextWindowPos(ImVec2(desktop_screen_width - 100, desktop_screen_height - 100));
		ImGui::SetNextWindowSize(ImVec2(100, 50));
		ImGui::Begin("Fullscreen", &window_output,
			ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
		ImGui::PlotHistogram("FPS", fps_values, IM_ARRAYSIZE(fps_values), 0, NULL, 0.0f, 100.0f, ImVec2(100, 50.0f));
		ImGui::TextUnformatted(fps_text.c_str());
		ImGui::End();

		// Now render
		ImGui::Render();

		// Show
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);

		// Save FPS to show a nice graph
		frame_count++;
		auto t = std::chrono::steady_clock::now();
		auto total_time = static_cast<float>((t - fps_clock).count());
		float fps = 1.0f / (total_time / 1000000000.0f);
		fps_values[fps_offset] = fps;
		fps_offset = (fps_offset + 1) % 64;
		fps_clock = std::chrono::steady_clock::now();
		fps_text = std::to_string((int)fps) + " FPS";

		// Do the game logic!
		world.Animate();
	}
}
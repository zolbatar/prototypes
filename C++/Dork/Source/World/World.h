#pragma once
#include <chrono>
#include <map>
#include <imgui.h>
#include "Physics.h"

class World
{
 public:
	void Reset();
	void Animate();
	void Render(const ImGuiViewport* main_viewport);

	b2World* GetBox2D()
	{
		return phys.GetWorld();
	}

 private:
	Physics phys;
	std::chrono::steady_clock::time_point clock;
	size_t millis = 0;
	size_t millis_per_step = 1000 / 60;

	// Render
	float zoom = 1.0;
};

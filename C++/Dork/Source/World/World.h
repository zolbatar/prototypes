#pragma once
#include <chrono>
#include <map>
#include <imgui.h>
#include "Physics.h"

class World
{
 public:
	void Reset();
	void Render();

	b2World* GetBox2D()
	{
		return phys.GetWorld();
	}

 private:
	Physics phys;
	std::chrono::steady_clock::time_point clock;
	size_t millis = 0;
	size_t millis_per_step = 1000 / 60;
};

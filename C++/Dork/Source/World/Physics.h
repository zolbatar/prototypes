#pragma once
#include <memory>
#include <box2d/box2d.h>

class Physics
{
 public:
	Physics();
	~Physics();
	void Simulate();
	b2World* GetWorld()
	{
		return world;
	}

 private:
	b2World* world;
	const float time_step = 1.0f / 60.0f;
	const int32 velocity_iterations = 6;
	const int32 position_iterations = 2;
};
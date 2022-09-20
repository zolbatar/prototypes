#include "World.h"
#include "Entity.h"
#include "Shape.h"

World* world;

void World::Reset()
{
	auto shape = Shape::CreateShape("Cube");
	shape->Cube(this, shape, 1.0f);
	Entity::CreateEntity(this, shape, b2Vec2(0.0f, 400.0f));
	clock = std::chrono::steady_clock::now();
}

void World::Animate()
{
	auto now = std::chrono::steady_clock::now();
	millis += std::chrono::duration_cast<std::chrono::milliseconds>(now - clock).count();
	while (millis > millis_per_step)
	{
		phys.Simulate();
		millis -= millis_per_step;
	}
	clock = now;
}

void World::Render(const ImGuiViewport* main_viewport)
{
	for (auto& entity : *Entity::GetEntities())
	{
		entity.Render(main_viewport);
	}
}

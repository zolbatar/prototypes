#include "World.h"
#include "Entity.h"
#include "Shapes/Shape.h"

World* world;

void World::Reset()
{
	auto shape = Shape::CreateShape("Cube");
	shape->Cube(this, shape, 1.0f);
	Entity::CreateEntity(this, shape, b2Vec2(0.0f, 4.0f));
	clock = std::chrono::steady_clock::now();
}

void World::Render()
{
	auto now = std::chrono::steady_clock::now();
	millis += std::chrono::duration_cast<std::chrono::milliseconds>(now - clock).count();
	while (millis > millis_per_step)
	{
		phys.Simulate();
		millis -= millis_per_step;
	}

	for (auto& entity : *Entity::GetEntities())
	{
		auto body = entity.GetBody();
		auto position = body->GetPosition();
		float angle = body->GetAngle();
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

	clock = now;
}
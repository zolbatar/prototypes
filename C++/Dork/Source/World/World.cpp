#include "World.h"
#include "Entity.h"
#include "Shapes/Shape.h"

World *world;

void World::Reset()
{
	world = new World();
	Shape::AddShape("Cube", Shape::Cube(this, 1.0f));
	Entity e(world, Shape::FindShape("Cube"), b2Vec2(0.0f, 4.0f));
	Entity::AddEntity(std::move(e));
	clock = std::chrono::steady_clock::now();
}

void World::Render()
{
	auto now = std::chrono::steady_clock::now();
	millis += std::chrono::duration_cast<std::chrono::milliseconds>(now - clock).count();
	while (millis > millis_per_step)
	{
		phys.Simulate();

		for (auto& entity : *Entity::GetEntities())
		{
			auto body = entity.second.GetBody();
			auto position = body->GetPosition();
			float angle = body->GetAngle();
			printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
		}

		millis -= millis_per_step;
	}
	clock = now;
}
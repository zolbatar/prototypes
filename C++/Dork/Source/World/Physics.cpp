#include <iostream>
#include "Physics.h"

Physics::Physics()
{
	auto gravity = b2Vec2(0.0f, -10.0f);
	world = new b2World(gravity);

	// Ground body
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
}

Physics::~Physics()
{
	delete world;
}

void Physics::Simulate()
{
	world->Step(time_step, velocity_iterations, position_iterations);
}

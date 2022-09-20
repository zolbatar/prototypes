#include "World.h"
#include "Entity.h"

std::list<Entity> Entity::entities;

Entity* Entity::CreateEntity(World* world, Shape* shape, b2Vec2 pos)
{
	entities.push_back(Entity(world, shape, pos));
	return &entities.back();
}

std::list<Entity>* Entity::GetEntities()
{
	return &entities;
}

Entity::Entity(World* world, Shape* shape, b2Vec2 pos)
{
	CreateBody(world, pos);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape->GetShape();
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
}

void Entity::CreateBody(World* world, b2Vec2 pos)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	body = world->GetBox2D()->CreateBody(&bodyDef);
}

b2Body* Entity::GetBody()
{
	return body;
}

void Entity::Render(const ImGuiViewport* main_viewport)
{
	auto body = GetBody();
	auto position = body->GetPosition();
	float angle = body->GetAngle();
	auto shape = body->GetFixtureList()->GetShape();
	printf("%4.2f %4.2f %4.2f %p\n", position.x, position.y, angle, shape);
}
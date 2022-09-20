#include "World.h"
#include "Entity.h"

size_t Entity::index = 0;
std::map<size_t, Entity> Entity::entities;

size_t Entity::AddEntity(Entity&& s)
{
	std::cout << "Create entity: " << index << std::endl;
	entities.emplace(std::make_pair(index++, std::move(s)));
	return index - 1;
}

std::map<size_t, Entity>* Entity::GetEntities()
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

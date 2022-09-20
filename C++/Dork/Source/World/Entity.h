#pragma once
#include <list>
#include <box2d/box2d.h>
#include "Shapes/Shape.h"

class Entity
{
public:
	Entity(World* world, Shape* shape, b2Vec2 pos);
	static Entity* CreateEntity(World* world, Shape* shape, b2Vec2 pos);
	static std::list<Entity>* GetEntities();
	b2Body* GetBody();

private:
	void CreateBody(World* world, b2Vec2 pos);

	b2Body* body;
	static std::list<Entity> entities;
};

#pragma once
#include <map>
#include <box2d/box2d.h>
#include "Shapes/Shape.h"

class Entity
{
 public:
	Entity(World* world, Shape* shape, b2Vec2 pos);
	static size_t AddEntity(Entity&& s);
	static std::map<size_t, Entity>* GetEntities();
	b2Body* GetBody();

 private:
	void CreateBody(World* world, b2Vec2 pos);

	b2Body* body;
	static size_t index;
	static std::map<size_t, Entity> entities;
};

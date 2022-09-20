#pragma once
#include <list>
#include <box2d/box2d.h>
#include "Shape.h"

class Entity
{
 public:
	Entity(World* world, Shape* shape, b2Vec2 pos);
	static Entity* CreateEntity(World* world, Shape* shape, b2Vec2 pos);
	static std::list<Entity>* GetEntities();
	b2Body* GetBody();
	void Render(const ImGuiViewport* main_viewport);

 private:
	void CreateBody(World* world, b2Vec2 pos);

	b2Body* body;
	static std::list<Entity> entities;
};

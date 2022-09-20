#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <box2d/box2d.h>
#include "../World.h"

class Shape
{
public:
	~Shape()
	{
		if (shape != nullptr)
			delete shape;
	}

	static void Cube(World* world, Shape* shape, float size)
	{
		auto ss = new b2PolygonShape();
		ss->SetAsBox(size, size);
		shape->SetShape(ss);
	}

	static Shape* CreateShape(std::string name)
	{
		shapes.emplace(std::make_pair(name, Shape()));
		return &shapes.find(name)->second;
	}

	static Shape* FindShape(std::string name)
	{
		return &shapes.find(name)->second;
	}

	b2Shape* GetShape()
	{
		return shape;
	}

	void SetShape(b2Shape* shape)
	{
		this->shape = shape;
	}

private:
	static std::map<std::string, Shape> shapes;
	b2Shape* shape = nullptr;
};

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
		delete shape;
	}

	static Shape Cube(World* world, float size)
	{
		Shape s;
		auto ss = new b2PolygonShape();
		ss->SetAsBox(size, size);
		s.SetShape(ss);
		return s;
	}

	static void AddShape(std::string name, Shape&& s)
	{
		std::cout << "Create shape: " << name << std::endl;
		shapes.emplace(std::make_pair(name, std::move(s)));
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
	b2Shape* shape;
};

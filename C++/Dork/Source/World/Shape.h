#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <box2d/box2d.h>
#include "World.h"

struct ShapePoint
{
	float x;
	float y;
};

class Shape
{
 public:
	~Shape();
	static void Cube(World* world, Shape* shape, float size);
	static Shape* CreateShape(std::string name);
	static Shape* FindShape(std::string name);
	b2Shape* GetShape();
	void SetShape(b2Shape* shape);
	void AddShapePoint(float x, float y);
	std::vector<ShapePoint> GetPoints();

 private:
	static std::map<std::string, Shape> shapes;
	std::vector<ShapePoint> points;
	b2Shape* shape = nullptr;
};

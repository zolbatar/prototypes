#include "Shape.h"

std::map<std::string, Shape> Shape::shapes;

Shape::~Shape()
{
	if (shape != nullptr)
		delete shape;
}

void Shape::Cube(World* world, Shape* shape, float size)
{
	auto ss = new b2PolygonShape();
	ss->SetAsBox(size, size);
	shape->SetShape(ss);
	shape->AddShapePoint(-size / 2, -size / 2);
	shape->AddShapePoint(size / 2, -size / 2);
	shape->AddShapePoint(size / 2, size / 2);
	shape->AddShapePoint(-size / 2, size / 2);
}

void Shape::AddShapePoint(float x, float y)
{
	points.push_back(ShapePoint{ x, y });
}

std::vector<ShapePoint> Shape::GetPoints()
{
	return points;
}

Shape* Shape::CreateShape(std::string name)
{
	shapes.emplace(std::make_pair(name, Shape()));
	return &shapes.find(name)->second;
}

Shape* Shape::FindShape(std::string name)
{
	return &shapes.find(name)->second;
}

b2Shape* Shape::GetShape()
{
	return shape;
}

void Shape::SetShape(b2Shape* shape)
{
	this->shape = shape;
}
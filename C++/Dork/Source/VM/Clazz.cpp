#include "Clazz.h"

Clazz::Clazz(std::string name, Clazz* parent)
	: name(name), parent(parent)
{
}

Method* Clazz::GetMethod(std::string name)
{
	// Do we have it here?
	auto f = methods.find(name);
	if (f != methods.end())
	{
		return &f->second;
	}

	// Try parent recursively
	if (parent != nullptr)
	{
		return parent->GetMethod(name);
	}
	return nullptr;
}

void Clazz::AddUnaryMethod(std::string name, void* func)
{
	methods.emplace(std::make_pair(name, Method(BytecodeType::Unary, func)));
}

void Clazz::AddMethodSubclassResponsibility(std::string name)
{
	methods.emplace(std::make_pair(name, Method(BytecodeType::Unknown, true)));
}



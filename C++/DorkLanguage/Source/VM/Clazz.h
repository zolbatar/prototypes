#pragma once
#include <map>
#include <string>
#include "Method.h"

class Clazz
{
 public:
	Clazz(std::string name, Clazz* parent);
	void AddUnaryMethod(std::string name, void* func);
	void AddMethodSubclassResponsibility(std::string name);
	Method* GetMethod(std::string name);

	std::string& GetName()
	{
		return name;
	}

 private:
	std::string name;
	Clazz* parent;
	std::map<std::string, Method> methods;
};

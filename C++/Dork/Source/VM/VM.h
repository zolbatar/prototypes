#pragma once
#include <map>
#include <list>
#include <string>
#include <memory>
#include "Clazz.h"
#include "Instance.h"

class VM
{
 public:
	VM();
	Instance* Integer(std::string name, Scope scope, int64_t v);
	Instance* Float(std::string name, Scope scope, double i);
	Clazz* FindClass(std::string name);

 private:
	Instance* AddGlobalInstance(Instance instance);
	Clazz* AddClass(std::string name, std::string parent);

	void InitNumber();
	void InitInteger();
	void InitFloat();

	std::map<std::string, Clazz> classes;
	std::list<Instance> global_instances;
	Clazz* class_integer;
	Clazz* class_float;
};

extern VM vm;

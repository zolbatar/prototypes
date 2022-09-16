#pragma once
#include <map>
#include <list>
#include <string>
#include <memory>
#include "Class.h"
#include "Instance.h"

class VM
{
 public:
	VM();
	std::shared_ptr<Instance> Integer(std::string name, Scope scope, int64_t v);
	std::shared_ptr<Instance> Float(std::string name, Scope scope, double i);
	std::shared_ptr<Class> FindClass(std::string name);

 private:
	std::shared_ptr<Instance> AddGlobalInstance(Instance instance);

	std::map<std::string, Class> classes;
	std::list<Instance> global_instances;
	std::shared_ptr<Class> class_integer;
	std::shared_ptr<Class> class_float;
};

extern VM vm;

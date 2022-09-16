#include "VM.h"
#include "../Exception/DorkException.h"

VM vm;

VM::VM()
{
	classes.emplace("Number", Class("Number", nullptr));
	classes.emplace("Integer", Class("Integer", FindClass("Number")));
	classes.emplace("Float", Class("Float", FindClass("Number")));
	class_integer = FindClass("Integer");
	class_float = FindClass("Float");
}

std::shared_ptr<Class> VM::FindClass(std::string name)
{
	if (!classes.contains(name))
	{
		return nullptr;
	}
	return std::make_shared<Class>(classes.find(name)->second);
}

std::shared_ptr<Instance> VM::AddGlobalInstance(Instance instance)
{
	global_instances.push_back(std::move(instance));
	return std::make_shared<Instance>(global_instances.back());
}

std::shared_ptr<Instance> VM::Integer(std::string name, Scope scope, int64_t v)
{
	auto i = Instance::Integer(class_integer, v);
	switch (scope)
	{
		case Scope::Global:
			return AddGlobalInstance(i);
		case Scope::Instance:
			assert(0);
	}
	return nullptr;
}

std::shared_ptr<Instance> VM::Float(std::string name, Scope scope, double v)
{
	auto i = Instance::Float(class_float, v);
	switch (scope)
	{
		case Scope::Global:
			return AddGlobalInstance(i);
		case Scope::Instance:
			assert(0);
	}
	return nullptr;
}

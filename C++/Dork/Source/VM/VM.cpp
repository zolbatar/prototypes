#include "VM.h"
#include "../Exception/DorkException.h"

VM vm;

VM::VM()
{
	auto clazz = AddClass("Object", "");
	clazz->AddMethodSubclassResponsibility("print");
	InitNumber();
}

Clazz* VM::AddClass(std::string name, std::string parent)
{
	classes.emplace(name, Clazz(name, FindClass(parent)));
	return FindClass(name);
}

Clazz* VM::FindClass(std::string name)
{
	if (!classes.contains(name))
	{
		return nullptr;
	}
	return &classes.find(name)->second;
}

Instance* VM::AddGlobalInstance(Instance instance)
{
	global_instances.push_back(std::move(instance));
	return &global_instances.back();
}

Instance* VM::Integer(std::string name, Scope scope, int64_t v)
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

Instance* VM::Float(std::string name, Scope scope, double v)
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

#include "VM.h"

VM vm;

void VM::CreateInteger(std::string name, int64_t v)
{
	if (dict_global.contains(name)) dict_global.erase(name);
	dict_global.emplace(std::make_pair(name, Object::CreateInteger(v)));
}

void VM::CreateDouble(std::string name, double v)
{
	if (dict_global.contains(name)) dict_global.erase(name);
	dict_global.emplace(std::make_pair(name, Object::CreateDouble(v)));
}

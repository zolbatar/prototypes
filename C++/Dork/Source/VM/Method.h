#pragma once
#include <string>
#include <vector>
#include "Bytecode.h"

class Method
{
 public:
	Method(BytecodeType type);
	Method(BytecodeType type, bool subclass_responsibility);
	Method(BytecodeType type, void* func);
	void AddCode(Bytecode&& code);
	void Run();

	BytecodeType GetType()
	{
		return type;
	}

	void* GetFunc()
	{
		return func;
	}

	bool NotImplemented()
	{
		return subclass_responsibility;
	}
 private:
	BytecodeType type;
	bool subclass_responsibility = false;
	void* func;
	std::vector<Bytecode> bytecodes;
};


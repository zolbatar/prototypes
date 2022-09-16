#pragma once
#include <vector>

enum BytecodeType
{
	Unknown,
	Unary,
	Binary,
	Keyword
};

struct Bytecode
{
	BytecodeType type;
	void* func;
	std::vector<void*> pars;
};
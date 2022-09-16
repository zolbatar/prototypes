#include "Method.h"

Method::Method(BytecodeType type)
	: type(type)
{
}

Method::Method(BytecodeType type, bool subclass_responsibility)
	: type(type), subclass_responsibility(subclass_responsibility)
{
}

Method::Method(BytecodeType type, void* func)
	: type(type), func(func)
{
}

void Method::AddCode(Bytecode&& code)
{
	bytecodes.push_back(std::move(code));
}

void Method::Run()
{
	for (auto& bc: bytecodes)
	{
		switch (bc.type)
		{
			case BytecodeType::Unary:
			{
				auto f = ((void (*)(void*))bc.func);
				f(bc.pars[0]);
				break;
			}
			default:
				assert(0);
		}
	}
}
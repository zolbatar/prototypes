#include "../../VM.h"

Instance* Integer_print(Instance* instance)
{
	return instance;
}

void VM::InitInteger()
{
	class_integer = AddClass("Integer", "Number");
	class_integer->AddUnaryMethod("print", (void*)&Integer_print);
}


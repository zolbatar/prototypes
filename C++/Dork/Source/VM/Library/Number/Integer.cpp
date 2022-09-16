#include "../../VM.h"

Instance* Integer_print(Instance* instance)
{
	int a = 1;
	return instance;
}

void VM::InitInteger()
{
	class_integer = AddClass("Integer", "Number");
	class_integer->AddUnaryMethod("print", (void*)&Integer_print);
}


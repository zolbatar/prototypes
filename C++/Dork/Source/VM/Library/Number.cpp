#include "../VM.h"

void VM::InitNumber()
{
	auto clazz = AddClass("Number", "Object");
	InitInteger();
	InitFloat();
}
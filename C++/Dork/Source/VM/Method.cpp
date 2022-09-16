#include "Method.h"

Method::Method()
{
}

Method::Method(bool subclass_responsibility)
	: subclass_responsibility(subclass_responsibility)
{
}

Method::Method(void* func)
	: unary_func(func)
{
}


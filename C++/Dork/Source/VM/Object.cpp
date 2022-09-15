#include "Object.h"

Object Object::CreateInteger(int64_t v)
{
	Object o;
	o.i_value = v;
	return o;
}

Object Object::CreateDouble(double v)
{
	Object o;
	o.f_value = v;
	return o;
}

#include "Instance.h"

Instance::Instance(Clazz* clazz)
	: clazz(clazz)
{
}

Instance Instance::Integer(Clazz* clazz, int64_t v)
{
	Instance o(clazz);
	o.i_value = v;
	return o;
}

Instance Instance::Float(Clazz* clazz, double v)
{
	Instance o(clazz);
	o.f_value = v;
	return o;
}

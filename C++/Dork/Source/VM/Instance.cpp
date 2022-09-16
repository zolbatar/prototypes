#include "Instance.h"

Instance::Instance(std::shared_ptr<Class> clazz)
	: clazz(clazz)
{

}

Instance Instance::Integer(std::shared_ptr<Class> clazz, int64_t v)
{
	Instance o(clazz);
	o.i_value = v;
	return o;
}

Instance Instance::Float(std::shared_ptr<Class> clazz, double v)
{
	Instance o(clazz);
	o.f_value = v;
	return o;
}

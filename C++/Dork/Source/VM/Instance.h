#pragma once
#include "Clazz.h"
#include <cstdint>

enum class Scope
{
	Global,
	Instance
};

class Instance
{
 public:
	Instance(Clazz* clazz);
	Clazz* GetClass()
	{
		return clazz;
	}
	static Instance Integer(Clazz* clazz, int64_t v);
	static Instance Float(Clazz* clazz, double v);

 private:
	Clazz* clazz;
	union
	{
		int64_t i_value;
		double f_value;
	};
};
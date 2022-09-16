#pragma once
#include "Class.h"
#include <cstdint>

enum class Scope
{
	Global,
	Instance
};

class Instance
{
 public:
	Instance(std::shared_ptr<Class> clazz);
	static Instance Integer(std::shared_ptr<Class> clazz, int64_t v);
	static Instance Float(std::shared_ptr<Class> clazz, double v);

 private:
	std::shared_ptr<Class> clazz;
	union
	{
		int64_t i_value;
		double f_value;
	};
};
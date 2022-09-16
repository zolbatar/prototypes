#pragma once
#include <string>
#include <functional>

class Method
{
 public:
	Method();
	Method(bool subclass_responsibility);
	Method(void* func);

	bool NotImplemented()
	{
		return subclass_responsibility;
	}
 private:
	bool subclass_responsibility = false;
	void* unary_func;
};


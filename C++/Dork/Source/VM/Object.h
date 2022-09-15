#pragma once
#include <cstdint>

class Object
{
 public:
	static Object CreateInteger(int64_t v);
	static Object CreateDouble(double v);

 private:
	union
	{
		int64_t i_value;
		double f_value;
	};
};

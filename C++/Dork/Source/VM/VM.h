#pragma once
#include <map>
#include <string>
#include "Object.h"

class VM
{
 public:
	void CreateInteger(std::string name, int64_t v);
	void CreateDouble(std::string name, double i);

 private:
	std::map<std::string, Object> dict_global;
};

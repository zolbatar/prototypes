#pragma once
#include <string>

class Class
{
 public:
	Class(std::string name, std::shared_ptr<Class> parent);

 private:
	std::string name;
	std::shared_ptr<Class> parent;
};

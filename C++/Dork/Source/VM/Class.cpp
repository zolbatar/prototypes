#include "Class.h"

Class::Class(std::string name, std::shared_ptr<Class> parent)
	: name(name), parent(parent)
{

}

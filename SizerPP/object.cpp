#include "object.h"

Object::Object(std::string name, Object* parrent) : name(new std::string(name)), parrent(parrent) {}
Object::Object(std::string name) : name(new std::string(name)), parrent(nullptr) {}

std::string Object::getFullPath()
{
	if (parrent)
		return parrent->getFullPath() + "/" + *name;
	return "C:/" + *name;
}
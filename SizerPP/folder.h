#include "object.h"

class Folder : public Object
{
	std::vector<Object*> objects;

public:
	Folder(std::string name, Object* parrent);
	Folder(std::string name);

	Folder* scan();
};
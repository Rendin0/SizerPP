#include "folder.h"

Folder::Folder(std::string name, Object* parrent) : Object(name, parrent) {}

Folder::Folder(std::string name) : Object(name) {}

Folder* Folder::scan()
{
	objects.clear();

	//for (const auto &i : std::filesystem::directory_iterator(std::filesystem::))

	return this;
}

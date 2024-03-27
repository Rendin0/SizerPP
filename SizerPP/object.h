#include <iostream>
#include <vector>
#include <filesystem>

class Object
{
protected:
	std::string* name;
	Object* parrent;

public:
	Object(std::string name, Object* parrent);
	Object(std::string name);

	std::string getFullPath();


};
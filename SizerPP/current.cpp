#include "current.h"

Current::Current(int mode)
{
	switch (mode)
	{
	case 0:
		path = std::filesystem::current_path().root_path();
		break;
	case 1:
		path = std::filesystem::current_path();
		break;
	default:
		path = std::filesystem::current_path();
		break;
	}
	folders = files = {};
	copy = "0";
}

std::filesystem::directory_entry Current::getEntry()
{
	return std::filesystem::directory_entry(path);
}

std::vector<std::filesystem::directory_entry>& Current::getFolders()
{
	return folders;
}

std::vector<std::filesystem::directory_entry>& Current::getFiles()
{
	return files;
}

std::filesystem::path& Current::getCopy()
{
	return copy;
}

uintmax_t Current::getAllSize()
{
	uintmax_t full_size = 0;

	for (auto entry : std::filesystem::recursive_directory_iterator(path))
	{
		full_size += entry.file_size();
	}
	return full_size;
}

std::filesystem::path& Current::getPath()
{
	return path;
}

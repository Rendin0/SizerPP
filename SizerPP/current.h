#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>

class Current
{
	std::filesystem::path path;
	std::vector<std::filesystem::directory_entry> folders;
	std::vector<std::filesystem::directory_entry> files;

public:
	Current(int mode);

	std::filesystem::directory_entry getEntry();
	std::vector<std::filesystem::directory_entry>& getFolders();
	std::vector<std::filesystem::directory_entry>& getFiles();

	uintmax_t getAllSize();
	std::filesystem::path& getPath();
	
};
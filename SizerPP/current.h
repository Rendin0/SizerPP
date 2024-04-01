#pragma once
#include <filesystem>
#include <iostream>

class Current
{
	std::filesystem::path path;


public:
	Current(int mode);

	std::filesystem::directory_entry getAll();
	uintmax_t getAllSize();
	std::filesystem::path& getPath();
};
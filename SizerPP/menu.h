#pragma once
#include "current.h"
#include <vector>
#include <conio.h>

void menu(Current& current);

std::filesystem::directory_entry menuPrint(std::vector<std::filesystem::directory_entry>& folders, std::vector<std::filesystem::directory_entry>& files, size_t& index);

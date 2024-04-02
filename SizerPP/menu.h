#pragma once
#include "current.h"
#include <vector>
#include <conio.h>
#include <string>

std::string byteConvert(uintmax_t bytes);

void menu(Current& current);

std::filesystem::directory_entry menuPrint(std::vector<std::filesystem::directory_entry>& folders, std::vector<std::filesystem::directory_entry>& files, size_t& index);

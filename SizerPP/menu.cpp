#include "menu.h"

std::string byteConvert(uintmax_t bytes)
{
	if (bytes / 1000000000 > 0)
		return "\033[3;33m" + std::to_string(bytes / 1000000000) + " GB\033[0m";
	else if (bytes > 1000000 > 0)
		return "\033[3;36m" + std::to_string(bytes / 1000000) + " MB\033[0m";
	else if (bytes / 1000 > 0)
		return "\033[3;35m" + std::to_string(bytes / 1000) + " KB\033[0m";
	else
		return "\033[3;34" + std::to_string(bytes) + " B\033[0m";
}

void menu(Current& current)
{
	size_t index = 0;

	current.getFolders() = current.getFiles() = {};

	current.getFolders().push_back(std::filesystem::directory_entry(current.getPath().string() + "\\.."));

	try
	{

		for (auto i : std::filesystem::directory_iterator(current.getPath()))
		{
			if (i.is_directory())
				current.getFolders().push_back(i);
			else
				current.getFiles().push_back(i);
		}
		system("cls");
	}
	catch (std::exception& e)
	{
		current.getPath() = std::filesystem::path(current.getPath().parent_path());
		std::cout << "\n" << e.what() << std::endl;
		system("pause");
		return;
	}

	if (current.getFiles().size() + current.getFolders().size() > 65)
	{
		std::cout << "Warning, a lot of files. Esc - exit, Any - continue";
		if (_getch() == 27)
		{
			current.getPath() = current.getPath().parent_path();
			return;
		}

	}

	std::cout << "^C-Copy ^V-Paste ^P-Path ^N-NewFile ^H-NewFolder ^R-Rename Del-Del\n\n";
	std::filesystem::directory_entry tmp = menuPrint(current.getFolders(), current.getFiles(), index);

	while (true)
	{
		size_t key = _getch();

		switch (key)
		{
		case 72:
			if (index == 0)
				index = current.getFolders().size() + current.getFiles().size() - 1;
			else
				index--;
			break;
		case 80:
			if (index >= current.getFiles().size() + current.getFolders().size() - 1)
				index = 0;
			else
				index++;
			break;
		case 16: // Ctrl + P
		{
			system("cls");
			std::cout << "Enter path: ";
			std::string tmp_str;
			std::getline(std::cin, tmp_str, '\n');
			current.getPath() = tmp_str;
			return;
		}
		case 3: // Ctrl + C
			current.getCopy() = tmp.path();
			break;
		case 22: // Ctrl + V
			if (current.getCopy() == "0")
				break;
			if (!std::filesystem::directory_entry(current.getCopy()).exists())
				break;

			std::filesystem::copy(current.getCopy(), current.getPath().string() + "\\" + current.getCopy().filename().string());

			return;
		case 7: // Ctrl + G

			break;
		case 14: // Ctrl + N
		{
			system("cls");
			std::cout << "Enter file name: ";
			std::string name;
			std::getline(std::cin, name);
			std::ofstream f(current.getPath().string() + "\\" + name);
			f.close();
			return;
		}
		case 8: // Ctrl + H
		{
			system("cls");
			std::cout << "Enter folder name: ";
			std::string name;
			std::getline(std::cin, name);
			std::filesystem::create_directory(current.getPath().string() + "\\" + name);
			return;
		}
		case 83: // Del
			std::filesystem::remove_all(tmp.path());
			return;
		case 18: // Ctrl + R
		{
			system("cls");
			std::cout << "Enter file name: ";
			std::string name;
			std::getline(std::cin, name);
			std::filesystem::rename(tmp.path(), tmp.path().parent_path().concat("\\" + name));
			return;
		}
		case 6: // Ctrl + F
			break;
		case 13: // Enter
			if (tmp.is_directory())
			{
				current.getPath() = tmp.path();
				return;
			}
			break;
		default:
			break;
		}

		std::cout << "\u001b[H";
		std::cout << "^C-Copy ^V-Paste ^P-Path ^N-NewFile ^H-NewFolder ^R-Rename Del-Del\n\n";
		tmp = menuPrint(current.getFolders(), current.getFiles(), index);

	}


}

std::filesystem::directory_entry menuPrint(std::vector<std::filesystem::directory_entry>& folders, std::vector<std::filesystem::directory_entry>& files, size_t& index)
{
	std::filesystem::directory_entry dir_to_return;


	for (size_t i = 0; i < folders.size(); i++)
	{
		if (index == i)
		{
			std::cout << "\u001b[48;5;17m";
			dir_to_return = folders.at(i);
		}
		std::cout << "\u001b[31;1m" << folders.at(i).path().filename().string() << "\u001b[0m" << std::endl;
	}

	for (size_t i = 0; i < files.size(); i++)
	{
		if (index == i + folders.size())
		{
			std::cout << "\u001b[48;5;17m";
			dir_to_return = files.at(i);
		}
		std::cout << files.at(i).path().filename().string()
			<< "\033[0m\033[50G"
			<< byteConvert(files.at(i).file_size())
			<< "\033[0m"
			<< "\033[100G"
			<< files.at(i).last_write_time() << std::endl;
	}

	if (index == 0)
		dir_to_return = std::filesystem::directory_entry(folders.at(0).path().parent_path().parent_path());

	return dir_to_return;
}

#include "menu.h"

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
		std::cout << "\n{Отказано в доступе}\n";
		current.getPath().concat("\\..");
		system("pause");
		return;
	}

	std::filesystem::directory_entry tmp = menuPrint(current.getFolders(), current.getFiles(), index);

	while (true)
	{
		if (_kbhit())
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

			case 13:
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
			tmp = menuPrint(current.getFolders(), current.getFiles(), index);

		}

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
		std::cout << files.at(i).path().filename().string() << "\u001b[0m" << std::endl;
	}

	return dir_to_return;
}

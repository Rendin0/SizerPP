#include "main.h"

int main()
{
	system("chcp 1251");

	Current curr(1);

	while (true)
	{
		menu(curr);
	}

	while (true)
		std::cout << _getch() << " ";

	return 0;
}
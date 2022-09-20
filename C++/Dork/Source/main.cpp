#include <iostream>
#include "UI/UI.h"

int main()
{
	std::cout << "Starting up Dork!" << std::endl;
	UI ui;
	ui.Loop();
	return 0;
}

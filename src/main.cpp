#include <exception>
#include <iostream>

#include <game/game.h>

int main()
{
	try
	{
		Game game;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		std::cin.get();
	}

	return 0;
}
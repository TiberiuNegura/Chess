#include "Game.h"
#include <memory>
#include <iostream>

int main()
{
	Game game;
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++) {
			game.GetElement(row, column) == nullptr ? std::cout<<"* " : std::cout << game.GetElement(row, column)->GetName() << " ";
		}
		std::cout << std::endl;
	}

	
	game.GetElement(1, 0)->Move({ 3, 0 }, game.GetGameboard());
	std::cout << "--------------------------------------------------------------------\n";
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++) {
			game.GetElement(row, column) == nullptr ? std::cout << "* " : std::cout << game.GetElement(row, column)->GetName() << " ";
		}
		std::cout << std::endl;
	}

	return 0;

	
}
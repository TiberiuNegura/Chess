#include "Game.h"
#include <memory>
#include <iostream>

int main()
{
	Game game;
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++) {
			game.getElement(row, column) == nullptr ? std::cout<<"* " : std::cout << game.getElement(row, column)->getName() << " ";
		}
		std::cout << std::endl;
	}

	
	std::cout << game.getElement(1, 0)->createPattern(game.GetGameboard()).size();

	return 0;

	
}
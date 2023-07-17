#include "Game.h"
#include "Board.h"
#include <memory>
#include <iostream>

void DisplayMatrix(Matrix& b)
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			auto tile = b[row][column];
			if (tile)
				std::cout << b[row][column]->GetName() << " ";
			else std::cout << "* ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	std::shared_ptr<IGame> game = std::make_shared<Game>();
	DisplayMatrix(game->GetBoard());
	game->MovePiece({ 6, 2 }, {4, 2});
	std::cout << std::endl;
	game->MovePiece({ 4, 2 }, {3, 2});
	std::cout << std::endl;
	game->MovePiece({ 3, 2 }, { 2, 2 });
	std::cout << std::endl;
	game->MovePiece({ 2, 2 }, { 1, 2 });
	DisplayMatrix(game->GetBoard());

	

	return 0;

	
}
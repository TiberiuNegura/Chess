#include "IGame.h"
#include "IPiece.h"
#include <iostream>

#include "Game.h"
#include "Board.h"
#include <memory>

void DisplayMatrix(MatrixPtr b)
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			auto tile = b->GetElement({ row, column });
			if (tile)
				std::cout << tile->GetName() << " ";
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
	game->MovePiece({ 3, 7 }, { 2, 6 });
	DisplayMatrix(game->GetBoard());

	

	return 0;

	
}
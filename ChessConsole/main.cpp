#include "IGame.h"
#include "IPiece.h"

#include "color.hpp"



void DisplayMatrix(MatrixPtr b)
{
	HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			auto tile = b->GetElement({ row, column });
			if (tile != nullptr)
			{
				if (tile->GetColor() == EColor::BLACK)
					std::cout << dye::aqua_on_black(tile->GetName()) << " ";
				else std::cout << dye::white_on_grey(tile->GetName()) << " ";
			}
			else
			{
				//SetConsoleTextAttribute(consoleColor, 2);
				std::cout << "* ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	std::shared_ptr<IGame> game = IGame::Produce();

	DisplayMatrix(game->GetBoard());
	game->MovePiece({ 6, 0 }, { 4, 0 });
	DisplayMatrix(game->GetBoard());
	
	

	return 0;

	
}
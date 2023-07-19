#include "IGame.h"
#include "IPiece.h"

#include "color.hpp"



void DisplayMatrix(MatrixPtr b)
{
	std::cout << "  ";
	for (int index = 0; index < 8; index++)
	{
		char letter = 'A' + index;
		std::cout << dye::yellow_on_black(letter) << " ";
	}
	std::cout << std::endl;
	for (int row = 0; row < 8; row++)
	{
		std::cout << dye::yellow_on_black(row+1) << " ";
		for (int column = 0; column < 8; column++)
		{
			auto tile = b->GetElement({ row, column });
			if (tile != nullptr)
			{
				if (tile->GetColor() == EColor::BLACK)
					std::cout << dye::grey_on_black(tile->GetName()) << " ";
				else std::cout << dye::white_on_black(tile->GetName()) << " ";
			}
			else
			{
				//SetConsoleTextAttribute(consoleColor, 2);
				std::cout << dye::green("* ");
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
	do
	{
		if (game->GetTurn() == EColor::WHITE)
			std::cout << dye::white_on_black("WHITE'S TURN\nInsert move: ");
		else 
			std::cout << dye::grey_on_black("BLACK'S TURN\nInsert move: ");
		char move[5];
		std::cin.getline(move, 6);
		try
		{
			game->MovePiece({move[1] - '1', move[0] - 'A' }, { move[4] - '1', move[3] - 'A' });
			DisplayMatrix(game->GetBoard());
		}
		catch (...)
		{
			std::cout << dye::red_on_black("Invalid move. Try again\n");
		}


	} while (!game->IsCheckmate(EColor::BLACK) && !game->IsCheckmate(EColor::WHITE));
	
	

	return 0;

	
}
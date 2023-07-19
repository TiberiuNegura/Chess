#include "IGame.h"
#include "IPiece.h"

#include "color.hpp"



void DisplayMatrix(MatrixPtr b)
{
	HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int index = 0; index < 8; index++)
	{
		char letter = 'A' + index;
		std::cout << letter << " ";
	}
	std::cout << std::endl;
	for (int row = 0; row < 8; row++)
	{
		std::cout << "row ";
		for (int column = 0; column < 8; column++)
		{
			auto tile = b->GetElement({ row, column });
			if (tile != nullptr)
			{
				if (tile->GetColor() == EColor::BLACK)
					std::cout << dye::yellow_on_black(tile->GetName()) << " ";
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
			std::cout << dye::yellow_on_black("BLACK'S TURN\nInsert move: ");
		char move[5];
		std::cin >> move;
		try
		{
			game->MovePiece({move[0]-'A', move[1] - '0'}, { move[3] - 'A', move[4] - '1' });
			DisplayMatrix(game->GetBoard());
		}
		catch (...)
		{
			std::cout << "Invalid move. Try again";
		}


	} while (!game->IsCheckmate(EColor::BLACK) && !game->IsCheckmate(EColor::WHITE));
	
	

	return 0;

	
}
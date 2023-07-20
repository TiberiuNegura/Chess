#include "IGame.h"
#include "IPiece.h"

#include "color.hpp"



void DisplayMatrix(MatrixPtr b)
{
	std::cout << " -------------------------------------\n |   | ";
	for (int index = 0; index < 8; index++)
	{
		char letter = 'A' + index;
		std::cout << dye::yellow_on_black(letter) << " | ";
	}
	std::cout << std::endl;
	std::cout << " -------------------------------------\n";
	for (int row = 0; row < 8; row++)
	{
		std::cout << " | " << dye::yellow_on_black(row + 1) << " | ";
		for (int column = 0; column < 8; column++)
		{
			auto tile = b->GetElement({ row, column });
			if (tile != nullptr)
			{
				if (tile->GetColor() == EColor::BLACK)
					std::cout << dye::grey_on_black(tile->GetName()) << " | ";
				else std::cout << dye::bright_white_on_black(tile->GetName()) << " | ";
			}
			else
			{
				//SetConsoleTextAttribute(consoleColor, 2);
				std::cout << dye::light_aqua(" ") << " | ";
			}
		}
		std::cout << std::endl;
		std::cout << " -------------------------------------\n";
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
		char move[10];
		std::cin.getline(move, 6);
		system("cls");
		try
		{
			game->MovePiece({ move[1] - '1', move[0] - 'A' }, { move[4] - '1', move[3] - 'A' });
		}
		catch (OutOfBoundsException e)
		{
			std::cout << dye::red_on_black(e.what()) << std::endl;
		}
		catch (EmptyPositionException e)
		{
			std::cout << dye::red_on_black(e.what()) << std::endl;
		}
		catch (PieceNotFoundException e)
		{
			std::cout << dye::red_on_black(e.what()) << std::endl;
		}
		catch (IllegalMoveException e)
		{
			std::cout << dye::red_on_black(e.what()) << std::endl;
		}
		DisplayMatrix(game->GetBoard());


	} while (!game->IsGameOver());
	
	

	return 0;

	
}
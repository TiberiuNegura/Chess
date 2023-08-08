#include "Status.h"
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
		std::string pieceOption;
		while (game->IsPawnEvolving())
		{
			std::cout << "What?\nYour pawn is evolving, choose a replacer between: queen, bishop, horse, rook.\nThe choice is yours: ";
			std::cin >> pieceOption; std::cin.ignore();
			try
			{
				if (pieceOption == "queen")
					game->EvolvePawn(EType::QUEEN);
				else if (pieceOption == "bishop")
					game->EvolvePawn(EType::BISHOP);
				else if (pieceOption == "horse")
					game->EvolvePawn(EType::HORSE);
				else if (pieceOption == "rook")
					game->EvolvePawn(EType::ROOK);
			}
			catch (PieceNotFoundException e)
			{
				std::cout << dye::red_on_black(e.what()) << std::endl;
			}
			system("cls");
			DisplayMatrix(game->GetBoard());
		}
		if (!game->IsTieRequest())
		{
			game->GetTurn() == EColor::WHITE ? std::cout << dye::white_on_black("WHITE'S TURN\n") : std::cout << dye::white_on_black("BLACKS'S TURN\n");
			std::cout << dye::white_on_black("Type `tie` for a tie request\nInsert move: ");
		}
		else
		{
			game->GetTurn() == EColor::WHITE ? std::cout << dye::white_on_black("WHITE'S TURN\n") : std::cout << dye::white_on_black("BLACKS'S TURN\n");
			std::cout << dye::white_on_black("A tie request has been sent\nInsert response (y/n): ");
		}
		std::string moveOption;
		std::getline(std::cin, moveOption);

		system("cls");
		try
		{
			if (moveOption == "tie" && !game->IsTieRequest())
			{
				game->MakeTieRequest();
				DisplayMatrix(game->GetBoard());
				continue;
			}
			else if (moveOption == "y" && game->IsTieRequest())
			{
				game->TieRequestResponse(true);
				DisplayMatrix(game->GetBoard());
				continue;
			}
			else if (moveOption == "n" && game->IsTieRequest())
			{
				game->TieRequestResponse(false);
				DisplayMatrix(game->GetBoard());
				continue;
			}
			game->MovePiece({ moveOption[1] - '1', moveOption[0] - 'A' }, { moveOption[4] - '1', moveOption[3] - 'A' });
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
		catch (CheckException e)
		{
			std::cout << dye::red_on_black(e.what()) << std::endl;
		}
		DisplayMatrix(game->GetBoard());


	} while (!game->IsGameOver());

	if (game->BlackWon())
		std::cout << "Black won the game!";
	else if (game->WhiteWon())
		std::cout << "White won the game!";
	else if (game->IsTie())
		std::cout << "Tie!";
	
	

	return 0;

	
}
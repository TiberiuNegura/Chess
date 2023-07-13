#include "Game.h"
#include "Board.h"
#include <memory>
#include <iostream>

int main()
{
	Board board;
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++) {
			board.GetGameBoard()[row][column] == nullptr ? std::cout<<"* " : std::cout << board.GetGameBoard()[row][column]->GetName() << " ";
		}
		std::cout << std::endl;
	}

	
	board.GetGameBoard()[1][0]->Move({ 3, 0 }, board.GetGameBoard());
	std::cout << "--------------------------------------------------------------------\n";
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++) {
			board.GetGameBoard()[row][column] == nullptr ? std::cout << "* " : std::cout << board.GetGameBoard()[row][column]->GetName() << " ";
		}
		std::cout << std::endl;
	}

	return 0;

	
}
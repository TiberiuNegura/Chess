#include "Game.h"
#include "Board.h"

// Constructor
Game::Game()
{
	board = std::make_shared<Board>();
}

void Game::StartGame()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Game::IsCheck()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Game::IsCheckmate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Game::MovePiece(Position start, Position destination)
{
	board->MoveOnBoard(start,destination);
}

Matrix& Game::GetBoard()
{
	return board->GetGameBoard();
}


#include "Game.h"
#include "Board.h"

// Constructor
Game::Game()
{
	m_board = std::make_shared<Board>();
}

void Game::StartGame()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Game::IsCheck(Position pos)
{
	/*auto king = m_board->GetGameBoard()[pos.first][pos.second];
	Color oppositeColor = king->GetColor() == Color::BLACK ? Color::WHITE : Color::BLACK;
	for (int i=0;i<8;i++)
		for (int j = 0; j < 8; j++)
		{
			if (m_board->GetGameBoard()[i][j] != king && )
		}*/
	return false;
}

bool Game::IsCheckmate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Game::MovePiece(Position start, Position destination)
{
	if (m_board->IsValid(start, destination))
		m_board->UpdatePosition(start, destination);
}

class CustomMatrix : public IMatrix
{
public:
	CustomMatrix(Matrix& mat)
		: m_board(mat)
	{ }
	IPiecePtr GetElement(Position element)
	{
		return m_board[element.first][element.second];
	}
private:
	Matrix& m_board;
};

MatrixPtr Game::GetBoard()
{
	return std::make_shared<CustomMatrix>(m_board->GetGameBoard());
}


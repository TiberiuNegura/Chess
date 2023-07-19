#include "Game.h"
#include "Board.h"

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}

// Constructor
Game::Game()
	: m_turn(EColor::WHITE)
{
	
}

bool Game::IsCheckmate(EColor color) const
{
	if (!m_board.IsCheck(color))
		return false;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			auto piece = m_board.GetGameBoard()[i][j];
			
			if (!piece) 
				continue;
			
			if (piece->GetColor() != color)
				continue;
			
			PositionList list = m_board.GetMoves({ i,j }, m_turn);
			if (!list.empty())
				return false;
		}
	return true;
}

void Game::MovePiece(Position start, Position destination)
{
	if (m_board.IsEmpty(start))
		throw EmptyPositionException();

	if (Board::IsOutOfBounds(start) || Board::IsOutOfBounds(destination))
		throw OutOfBoundsException();

	PositionList positions = m_board.GetMoves(start, m_turn); // creates pattern

	for (auto& position : positions)
		if (position == destination)
		{
			m_board.MovePiece(start, destination);
			m_turn = (m_turn == EColor::WHITE ? EColor::BLACK : EColor::WHITE);
			return;
		}

	throw IllegalMoveException();
}

class CustomMatrix : public IMatrix
{
public:
	CustomMatrix(const Matrix& mat)
		: m_board(mat)
	{ }
	IPiecePtr GetElement(Position element)
	{
		return m_board[element.first][element.second];
	}
private:
	const Matrix& m_board;
};

MatrixPtr Game::GetBoard() const
{
	return std::make_shared<CustomMatrix>(m_board.GetGameBoard());
}


EColor Game::GetTurn() const
{
	return m_turn;
}


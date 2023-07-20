#include "Game.h"
#include "Board.h"

#include "CheckException.h"
#include "InvalidOptionException.h"

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}

// Constructor
Game::Game()
	: m_turn(EColor::WHITE)
{
	
}

Game::Game(std::array<std::array<char, 8>, 8> mat, EColor turn)
	: m_board(mat)
	, m_turn(turn)
{
}

void Game::MovePiece(Position start, Position destination)
{
	if (m_board.IsEmptyPosition(start))
		throw EmptyPositionException();

	if (Board::IsOutOfBounds(start) || Board::IsOutOfBounds(destination))
		throw OutOfBoundsException();

	PositionList positions = GetMoves(start); // creates pattern

	for (auto& position : positions)
		if (position == destination)
		{
			m_board.MovePiece(start, destination);
			ChangeTurn();
			return;
		}

	throw IllegalMoveException();
}


void Game::ChangeTurn()
{
	m_turn = (m_turn == EColor::WHITE ? EColor::BLACK : EColor::WHITE);
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
	return std::make_shared<CustomMatrix>(m_board.GetMatrix());
}

EColor Game::GetTurn() const
{
	return m_turn;
}

PositionList Game::GetMoves(Position piecePos) const
{
	return m_board.GetMoves(piecePos, m_turn);
}

bool Game::IsGameOver() const
{
	return (m_board.IsCheckmate(EColor::WHITE) || m_board.IsCheckmate(EColor::BLACK));
}

void Game::MakeCastling(std::string where)
{
	if (m_board.IsCheck(m_turn))
		throw CheckException();
	
	if (where != "left" && where != "right")
		throw InvalidOptionException();

	m_board.Castling(m_turn, where);
	ChangeTurn();
}


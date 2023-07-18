#include "Game.h"
#include "Board.h"
#include "OutOfBoundsException.h"
#include "PieceNotFoundException.h"

// Constructor
Game::Game()
{
	m_board = std::make_shared<Board>();
}

void Game::StartGame()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Game::IsCheck(Color color)
{
	Color oppositeColor = color == Color::BLACK ? Color::WHITE : Color::BLACK;
	auto king = FindKing(color);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (m_board->GetGameBoard()[i][j]->GetColor() == oppositeColor)
			{
				PositionList list = m_board->PatternValidation({ i,j }, m_board->GetGameBoard()[i][j]->CreatePattern());
				for (auto position : list)
				{
					if (position == king)
						return true;
				}
			}
		}
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

PositionList Game::GetPattern(Position piecePos)
{
	if (Board::IsOutOfBounds(piecePos.first, piecePos.second)) throw OutOfBoundsException();
	auto piece = m_board->GetGameBoard()[piecePos.first][piecePos.second];
	if (!piece) throw PieceNotFoundException();
	PositionList pattern = m_board->PatternValidation(piecePos, piece->CreatePattern());
	auto king = FindKing(piece->GetColor());
	for (auto pos : pattern)
	{

	}

}

Position Game::FindKing(Color color)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			auto currentPiece = m_board->GetGameBoard()[i][j];
			if (currentPiece->GetColor() == color && currentPiece->GetType() == Type::KING)
				return { i, j };
		}
	throw PieceNotFoundException();
}


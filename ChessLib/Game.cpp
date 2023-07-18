#include "Game.h"
#include "Board.h"
#include "PieceNotFoundException.h"
#include "OutOfBoundsException.h"
#include "IllegalMoveException.h"
#include "EmptyPositionException.h"

IGamePtr IGame::StartGame()
{
	return std::make_shared<Game>();
}

// Constructor
Game::Game()
{
	m_board = std::make_shared<Board>();
	m_turn = Color::WHITE;
}


bool Game::IsCheck(Color color)
{
	Color oppositeColor = color == Color::BLACK ? Color::WHITE : Color::BLACK;
	auto king = FindKing(color);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			auto piece = m_board->GetGameBoard()[i][j];
			if (piece) 
			{
				if (piece->GetColor() == oppositeColor)
				{
					PositionList list = m_board->PatternValidation({ i,j }, m_board->GetGameBoard()[i][j]->CreatePattern());
					for (auto position : list)
					{
						if (position == king)
							return true;
					}
				}
			}
		}
	return false;
}

bool Game::IsCheckmate(Color color)
{
	if (!IsCheck(color)) return false;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			auto piece = m_board->GetGameBoard()[i][j];
			if (!piece) continue;
			if (piece->GetColor() != color) continue;
			PositionList list = GetPattern({ i,j });
			if (!list.empty())
				return false;
		}
	return true;
}

void Game::MovePiece(Position start, Position destination)
{
	if (IsValid(start, destination))
	{
		m_board->UpdatePosition(start, destination);
		m_turn == Color::WHITE ? Color::BLACK : Color::WHITE;
	}
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
	if (piece->GetColor() != m_turn)
		return PositionList(); // or throw, it needs to be discussed (possible NotYourTurn exception)
	PositionList pattern = m_board->PatternValidation(piecePos, piece->CreatePattern());
	auto king = FindKing(piece->GetColor());
	for (auto it = pattern.begin(); it != pattern.end();)
	{
		Position current = *it;
		auto aux = m_board->GetGameBoard()[current.first][current.second];
		m_board->UpdatePosition(piecePos, current); // simulate the move
		if (IsCheck(piece->GetColor()))
			it = pattern.erase(it);
		else
			++it;
		m_board->UpdatePosition(current, piecePos); // rollback to initial position
		m_board->RevertPosition(aux);
	}
	return pattern;
}

bool Game::IsValid(Position start, Position end)
{
	if (!m_board->GetGameBoard()[start.first][start.second]) throw EmptyPositionException();
	if (Board::IsOutOfBounds(start.first, start.second)) throw OutOfBoundsException();
	if (Board::IsOutOfBounds(end.first, end.second)) throw OutOfBoundsException();
	PositionList pattern = GetPattern(start); // creates pattern
	for (auto& position : pattern)
		if (position == end)
			return true;
	throw IllegalMoveException();
}

Color Game::GetTurn()
{
	return m_turn;
}

Position Game::FindKing(Color color)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			auto currentPiece = m_board->GetGameBoard()[i][j];
			if (currentPiece)
			{
				if (currentPiece->GetColor() == color && currentPiece->GetType() == Type::KING)
					return { i, j };
			}
		}
	throw PieceNotFoundException();
}


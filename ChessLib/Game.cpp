#include "Game.h"

#include "Board.h"
#include "PieceNotFoundException.h"
#include "OutOfBoundsException.h"
#include "IllegalMoveException.h"
#include "EmptyPositionException.h"

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}

// Constructor
Game::Game()
	: m_turn(EColor::WHITE)
	, m_board(std::make_shared<Board>())
{
	
}


bool Game::IsCheck(EColor color) const
{
	EColor oppositeColor = color == EColor::BLACK ? EColor::WHITE : EColor::BLACK;
	
	auto kingPos = FindKing(color);
	
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (auto piece = m_board->GetGameBoard()[i][j])
			{
				if (piece->GetColor() == oppositeColor)
				{
					PositionList list = m_board->ComputePositionList({ i,j }, piece->GetDirections());
					for (auto position : list)
					{
						if (position == kingPos)
							return true;
					}
				}
			}
		}
	return false;
}

bool Game::IsCheckmate(EColor color) const
{
	if (!IsCheck(color))
		return false;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			auto piece = m_board->GetGameBoard()[i][j];
			
			if (!piece) 
				continue;
			
			if (piece->GetColor() != color)
				continue;
			
			PositionList list = GetMoves({ i,j });
			if (!list.empty())
				return false;
		}
	return true;
}

void Game::MovePiece(Position start, Position destination)
{
	if (m_board->IsEmpty(start))
		throw EmptyPositionException();

	if (Board::IsOutOfBounds(start) || Board::IsOutOfBounds(destination))
		throw OutOfBoundsException();

	PositionList positions = GetMoves(start); // creates pattern
	for (auto& position : positions)
		if (position == destination)
		{
			m_board->UpdatePosition(start, destination);

			m_turn = (m_turn == EColor::WHITE ? EColor::BLACK : EColor::WHITE);
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
	return std::make_shared<CustomMatrix>(m_board->GetGameBoard());
}

PositionList Game::GetMoves(Position piecePos) const
{
	if (Board::IsOutOfBounds(piecePos)) 
		throw OutOfBoundsException();
	
	auto piece = m_board->GetGameBoard()[piecePos.first][piecePos.second];
	
	if (!piece || piece->GetColor() != m_turn)
		return PositionList();

	PositionList positions = m_board->ComputePositionList(piecePos, piece->GetDirections());

	auto king = FindKing(m_turn);

	for (auto it = positions.begin(); it != positions.end();)
	{
		Position current = *it;
		auto aux = m_board->GetGameBoard()[current.first][current.second];
		m_board->UpdatePosition(piecePos, current); // simulate the move
		if (IsCheck(piece->GetColor()))
			it = positions.erase(it);
		else
			++it;
		m_board->UpdatePosition(current, piecePos); // rollback to initial position
		m_board->RevertPosition(aux);
	}

	return positions;
}

EColor Game::GetTurn() const
{
	return m_turn;
}

Position Game::FindKing(EColor color) const
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			auto currentPiece = m_board->GetGameBoard()[i][j];
			if (currentPiece)
			{
				if (currentPiece->GetColor() == color && currentPiece->GetType() == EType::KING)
					return { i, j };
			}
		}
	throw PieceNotFoundException();
}


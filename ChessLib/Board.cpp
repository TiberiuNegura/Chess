#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Horse.h"
#include "Queen.h"
#include "King.h"
#include "Piece.h"

Board::Board()
{
	// Board initialize

	// Pawns
	for (int column = 0; column < 8; column++) {
		m_board[1][column] = std::make_shared<Pawn>(1, column, Color::BLACK);
		m_board[6][column] = std::make_shared<Pawn>(6, column, Color::WHITE);
	}

	// Rooks
	m_board[0][0] = std::make_shared<Rook>(0, 0, Color::BLACK);
	m_board[0][7] = std::make_shared<Rook>(0, 7, Color::BLACK);
	m_board[7][0] = std::make_shared<Rook>(7, 0, Color::WHITE);
	m_board[7][7] = std::make_shared<Rook>(7, 7, Color::WHITE);

	// Horses
	m_board[0][1] = std::make_shared<Horse>(0, 1, Color::BLACK);
	m_board[0][6] = std::make_shared<Horse>(0, 6, Color::BLACK);
	m_board[7][1] = std::make_shared<Horse>(7, 1, Color::WHITE);
	m_board[7][6] = std::make_shared<Horse>(7, 6, Color::WHITE);

	// Bishops
	m_board[0][2] = std::make_shared<Bishop>(0, 2, Color::BLACK);
	m_board[0][5] = std::make_shared<Bishop>(0, 5, Color::BLACK);
	m_board[7][2] = std::make_shared<Bishop>(7, 2, Color::WHITE);
	m_board[7][5] = std::make_shared<Bishop>(7, 5, Color::WHITE);

	// Queens
	m_board[0][3] = std::make_shared<Queen>(0, 3, Color::BLACK);
	m_board[7][3] = std::make_shared<Queen>(7, 3, Color::WHITE);

	// Kings
	m_board[0][4] = std::make_shared<King>(0, 4, Color::BLACK);
	m_board[7][4] = std::make_shared<King>(7, 4, Color::WHITE);
}

Matrix& Board::GetGameBoard()
{
	return m_board;
}

void Board::MoveOnBoard(Position start, Position destination)
{
	//TODO: implement exception
}

PositionList Board::PatternValidation(Position start, std::vector<PositionList> positions)
{
	Type type = m_board[2][2]->GetType();
	switch (type)
	{
	case Type::PAWN:

		break;
	case Type::BISHOP:
		break;
	case Type::HORSE:
		break;
	case Type::KING:
		break;
	case Type::QUEEN:
		break;
	case Type::ROOK:
		break;
	}
	if (m_board[2][2]->GetType() == Type::BISHOP) {}
	return PositionList();
}

bool Board::IsValid(Position start, Position end)
{
	throw std::logic_error("The method or operation is not implemented.");
}

PositionList Board::PawnPattern(Position start, std::vector<PositionList> pawnMoves)
{
	PositionList pattern;
	auto pawn = m_board[start.first][start.second];
	int row = start.first, column = start.second;
	int nextPos = (pawn->GetColor() == Color::WHITE) ? -1 : 1;
	for (auto positions : pawnMoves)
	{
		for (auto position : positions)
		{
			if (!m_board[position.first][position.second])
				pattern.push_back(position);
		}
	}
	if (!Piece::IsOutOfBounds(row + nextPos, column))
	{
		/*auto elem = board[row + nextPos][column + pow(-1, sign)];
					if (elem && elem->GetColor() != GetColor())
					{
						Position pos = { row + nextPos, column + pow(-1, sign) };
						positions.emplace_back(pos);
					}*/

	}

	return pattern;
}

PositionList Board::HorsePattern(Position start, std::vector<PositionList> horseMoves)
{
	return PositionList();
}

PositionList Board::KingPattern(Position start, std::vector<PositionList> kingMoves)
{
	return PositionList();
}

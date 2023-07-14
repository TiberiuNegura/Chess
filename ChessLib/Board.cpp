#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Horse.h"
#include "Queen.h"
#include "King.h"
#include "Piece.h"
#include "OutOfBoundsException.h"
#include "IllegalMoveException.h"

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

	// Testing pieces
	m_board[4][4] = std::make_shared<Bishop>(4, 4, Color::BLACK);
}

Matrix& Board::GetGameBoard()
{
	return m_board;
}

void Board::MoveOnBoard(Position start, Position destination)
{
	if (IsValid(start, destination))
	{
		m_board[destination.first][destination.second] = m_board[start.first][start.second];
		m_board[start.first][start.second] = nullptr;
		m_board[destination.first][destination.second]->SetPosition(destination);
	}
}

PositionList Board::PatternValidation(Position start, std::vector<PositionList> positions)
{
	Type pieceType = m_board[start.first][start.second]->GetType();
	switch (pieceType)
	{
	case Type::PAWN:
		break;
	case Type::QUEEN:
	case Type::ROOK:
	case Type::BISHOP:
		return DynamicValidation(start, positions);
	case Type::HORSE:
		break;
	case Type::KING:
		break;
	}
	throw std::exception("i don't know this error yet");
}

bool Board::IsValid(Position start, Position end)
{
	if (IsOutOfBounds(start.first, start.second)) throw OutOfBoundsException();
	if (IsOutOfBounds(end.first, end.second)) throw OutOfBoundsException();
	PositionList pattern = PatternValidation(start, m_board[start.first][start.second]->CreatePattern()); // creates pattern
	for (auto& position : pattern)
		if (position == end)
			return true;
	throw IllegalMoveException();
}

PositionList Board::DynamicValidation(Position start, std::vector<PositionList> positions)
{
	PositionList validPattern;
	Color pieceColor = m_board[start.first][start.second]->GetColor();
	for (int direction = 0; direction < positions.size(); direction++)
	{
		for (int tile = 0; tile < positions[direction].size(); tile++)
		{
			int row = positions[direction][tile].first, column = positions[direction][tile].second;
			if (IsOutOfBounds(row, column))
				continue;
			auto possiblePosition = m_board[row][column];
			if (!possiblePosition)
				validPattern.emplace_back(row, column);
			else
			{
				Color obstacleColor = possiblePosition->GetColor();
				if (obstacleColor != pieceColor)
					validPattern.emplace_back(row, column);
				break;
			}
		}
	}
	return validPattern;
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
	if (!Board::IsOutOfBounds(row + nextPos, column))
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

bool Board::IsOutOfBounds(int row, int column)
{
	return !(0 <= row && row < 8 && 0 <= column && column < 8);
}

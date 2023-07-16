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
		// disable isFirstMove on Pawn

	}
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

PositionList Board::PatternValidation(Position start, std::vector<PositionList> positions)
{
	PositionList validPattern;
	Color pieceColor = m_board[start.first][start.second]->GetColor();
	Type pieceType = m_board[start.first][start.second]->GetType();
	for (int direction = 0; direction < positions.size(); direction++)
	{
		for (int tile = 0; tile < positions[direction].size(); tile++)
		{
			int row = positions[direction][tile].first, column = positions[direction][tile].second;
			if (IsOutOfBounds(row, column))
				continue;
			auto possiblePosition = m_board[row][column];
			if (!possiblePosition)
			{
				if (pieceType == Type::PAWN && positions[direction].size() - tile <= 2) 
					break; // if pawn and diagonal path is empty, skip the 2 diagonal path considering isFirstMove
				validPattern.emplace_back(row, column);
			}
			else
			{
				Color obstacleColor = possiblePosition->GetColor();
				if (obstacleColor != pieceColor)
					validPattern.emplace_back(row, column);
				if (pieceType == Type::HORSE || pieceType == Type::PAWN || pieceType == Type::KING)
					continue;
				else
					break;
			}
		}
	}
	return validPattern;
}

bool Board::IsOutOfBounds(int row, int column)
{
	return !(0 <= row && row < 8 && 0 <= column && column < 8);
}

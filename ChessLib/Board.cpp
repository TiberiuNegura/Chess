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
		m_board[1][column] = std::make_shared<Pawn>(1, column, EColor::BLACK);
		m_board[6][column] = std::make_shared<Pawn>(6, column, EColor::WHITE);
	}

	// Rooks
	m_board[0][0] = std::make_shared<Rook>(0, 0, EColor::BLACK);
	m_board[0][7] = std::make_shared<Rook>(0, 7, EColor::BLACK);
	m_board[7][0] = std::make_shared<Rook>(7, 0, EColor::WHITE);
	m_board[7][7] = std::make_shared<Rook>(7, 7, EColor::WHITE);

	// Horses
	m_board[0][1] = std::make_shared<Horse>(0, 1, EColor::BLACK);
	m_board[0][6] = std::make_shared<Horse>(0, 6, EColor::BLACK);
	m_board[7][1] = std::make_shared<Horse>(7, 1, EColor::WHITE);
	m_board[7][6] = std::make_shared<Horse>(7, 6, EColor::WHITE);

	// Bishops
	m_board[0][2] = std::make_shared<Bishop>(0, 2, EColor::BLACK);
	m_board[0][5] = std::make_shared<Bishop>(0, 5, EColor::BLACK);
	m_board[7][2] = std::make_shared<Bishop>(7, 2, EColor::WHITE);
	m_board[7][5] = std::make_shared<Bishop>(7, 5, EColor::WHITE);

	// Queens
	m_board[0][3] = std::make_shared<Queen>(0, 3, EColor::BLACK);
	m_board[7][3] = std::make_shared<Queen>(7, 3, EColor::WHITE);

	// Kings
	m_board[0][4] = std::make_shared<King>(0, 4, EColor::BLACK);
	m_board[7][4] = std::make_shared<King>(7, 4, EColor::WHITE);

}

const Matrix& Board::GetGameBoard() const
{
	return m_board;
}

bool Board::IsEmpty(Position p) const
{
	if (m_board[p.first][p.second])
		return true;
	return false;
}

PositionList Board::ComputePositionList(Position start, std::vector<PositionList> positions)
{
	PositionList validPattern;
	EColor pieceColor = m_board[start.first][start.second]->GetColor();
	EType pieceType = m_board[start.first][start.second]->GetType();
	for (int direction = 0; direction < positions.size(); direction++)
	{
		for (int tile = 0; tile < positions[direction].size(); tile++)
		{
			int row = positions[direction][tile].first;
			int column = positions[direction][tile].second;

			if (IsOutOfBounds(positions[direction][tile]))
				continue;
			
			
			if (auto possiblePosition = m_board[row][column])
			{
				EColor obstacleColor = possiblePosition->GetColor();
				if (pieceType == EType::PAWN && abs(start.first - row) == 1 && abs(start.second - column) == 0)
					continue; // pawn can't overtake a frontal piece
				if (obstacleColor != pieceColor)
					validPattern.emplace_back(row, column);
				if (pieceType == EType::HORSE || pieceType == EType::PAWN || pieceType == EType::KING)
					continue; // if horse, pawn or king, continue to next position
				else
					break; // if queen, bishop or rook, break the tile loop when adversary piece found
			}
			else
			{
				if (pieceType == EType::PAWN && abs(start.first - row) == 1 && abs(start.second - column) == 0)
					continue; // if pawn and diagonal path is empty, skip the 2 diagonal path considering isFirstMove
				validPattern.emplace_back(row, column);
			}
		}
	}
	return validPattern;
}

void Board::UpdatePosition(Position start, Position end)
{
	m_board[end.first][end.second] = m_board[start.first][start.second];
	m_board[start.first][start.second] = {};
	m_board[end.first][end.second]->SetPosition(end);
}

void Board::RevertPosition(PiecePtr toRevert)
{
	if (toRevert)
	{
		auto pos = toRevert->GetPosition();
		m_board[pos.first][pos.second] = toRevert;
	}
}

bool Board::IsOutOfBounds(Position p)
{
	return !(0 <= p.first && p.first < 8 && 0 <= p.second && p.second < 8);
}

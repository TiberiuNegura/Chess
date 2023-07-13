#include "Pawn.h"

// Constructor
Pawn::Pawn(
	int row,
	int column,
	Color color
) : Piece('P', row, column, color, Type::PAWN)
  , isFirstMove(true)
{ }


// PieceInterface implemented methods
void Pawn::Move(Position destination, Matrix& board)
{
	if (!IsValid(destination, board))
		throw std::exception("Not a valid move!");
	board[destination.first][destination.second] = board[m_position.first][m_position.second];
	board[m_position.first][m_position.second] = nullptr;
	m_position = destination;
	if (isFirstMove)
		isFirstMove = false;
}

bool Pawn::IsValid(Position destination, const Matrix& board) const
{
	PositionList positions = CreatePattern(board);
	for (auto& pos : positions) 
	{
		if (destination == pos)
			return true;
	}
	return false;
}

PositionList Pawn::CreatePattern(const Matrix& board) const
{
	PositionList positions;
	int row = m_position.first, column = m_position.second;
	int nextPos = (m_color == Color::WHITE) ? -1 : 1;

	if (!Piece::IsOutOfBounds(row + nextPos, column))
	{
		auto elem = board[row + nextPos][column];
		if (!elem)
		{
			Position pos = { row + nextPos, column };
			positions.emplace_back(pos);
			if (!Piece::IsOutOfBounds(pos.first + nextPos, pos.second))
			{
				auto elem = board[pos.first + nextPos][pos.second];
				if (isFirstMove && !elem)
					positions.emplace_back(pos);
			}
		}
	}

	for (int sign = 0; sign < 2; sign++)
	{
		if (!Piece::IsOutOfBounds(row + nextPos, column + pow(-1, sign))) 
		{
			auto elem = board[row + nextPos][column + pow(-1, sign)];
			if (elem && elem->GetColor() != GetColor())
			{
				Position pos = { row + nextPos, column + pow(-1, sign) };
				positions.emplace_back(pos);
			}
		}
	}

	return positions;
}

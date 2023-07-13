#include "Pawn.h"
Pawn::Pawn(
	int row,
	int column,
	Color color
) : Piece('P', row, column, color, Type::PAWN)
  , isFirstMove(true)
{
}

void Pawn::move(Position destination, Matrix& board)
{
	// if can move, don't forget to disable isFirstMove
}

bool Pawn::isValid(Position destination, const Matrix& board)
{
	return false;
}

PositionList Pawn::createPattern(const Matrix& board)
{
	PositionList positions;
	int row = m_position.first, column = m_position.second;
	int nextPos = (m_color == Color::WHITE) ? -1 : 1;

	auto elem = board[row + nextPos][column];
	if (!elem)
	{
		Position pos = { row + nextPos, column };
		positions.emplace_back(pos);
		auto elem = board[pos.first + nextPos][pos.second];
		if (isFirstMove && !elem)
			positions.emplace_back(pos);
	}
	for (int sign = 0; sign < 2; sign++)
	{
		if (row + nextPos > 0 && column + pow(-1, sign) > 0) // more conditions to implement. maybe OutOfBound method to check?
		{
			elem = board[row + nextPos][column + pow(-1, sign)];
			if (elem && elem->getColor() != getColor())
			{
				Position pos = { row + nextPos, column + pow(-1, sign) };
				positions.emplace_back(pos);
			}
		}
	}


	return positions;
}

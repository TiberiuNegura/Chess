#include "King.h"



King::King(
	int row,
	int column,
	Color color
) : Piece('K', row, column, color, Type::KING)
{
}

void King::move(Position destination, Matrix& board)
{
}

bool King::isValid(Position destination, const Matrix& board)
{
	return false;
}

PositionList King::createPattern(const Matrix& board)
{
	return PositionList();
}


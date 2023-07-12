#include "Horse.h"


Horse::Horse(
	int row,
	int column,
	Color color
) : Piece('H', row, column, color, Type::HORSE)
{
}

void Horse::move(Position destination, Matrix& board)
{
}

bool Horse::isValid(Position destination, const Matrix& board)
{
	return false;
}

PositionList Horse::createPattern(const Matrix& board)
{
	return PositionList();
}



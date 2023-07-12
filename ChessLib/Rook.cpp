#include "Rook.h"

Rook::Rook(
	int row,
	int column,
	Color color
) : Piece('R', row, column, color, Type::ROOK)
{

}

void Rook::move(Position destination, Matrix& board)
{
}

bool Rook::isValid(Position destination, const Matrix& board)
{
	return false;
}

PositionList Rook::createPattern(const Matrix& board)
{
	return PositionList();
}


#include "King.h"

// Constructor
King::King(
	int row,
	int column,
	Color color
) : Piece('K', row, column, color, Type::KING)
{ }

// PieceInterface implemented methods
void King::Move(Position destination, Matrix& board)
{

}

bool King::IsValid(Position destination, const Matrix& board) const
{
	return false;
}

PositionList King::CreatePattern(const Matrix& board) const
{
	return PositionList();
}


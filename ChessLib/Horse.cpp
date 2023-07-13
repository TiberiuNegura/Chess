#include "Horse.h"

// Constructor
Horse::Horse(
	int row,
	int column,
	Color color
) : Piece('H', row, column, color, Type::HORSE)
{
}

// PieceInterface implemented methods
void Horse::Move(Position destination, Matrix& board)
{

}

bool Horse::IsValid(Position destination, const Matrix& board) const
{
	return false;
}

PositionList Horse::CreatePattern(const Matrix& board) const
{
	return PositionList();
}



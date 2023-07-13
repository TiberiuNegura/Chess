#include "Rook.h"

// Constructor
Rook::Rook(
	int row,
	int column,
	Color color
) : Piece('R', row, column, color, Type::ROOK)
{ }


// PieceInterface implemented methods
void Rook::Move(Position destination, Matrix& board)
{

}

bool Rook::IsValid(Position destination, const Matrix& board) const
{
	return false;
}

PositionList Rook::CreatePattern(const Matrix& board) const
{
	return PositionList();
}


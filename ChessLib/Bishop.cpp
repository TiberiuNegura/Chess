#include "Bishop.h"

// Constructor
Bishop::Bishop(
    int row,
    int column,
    Color color
) : Piece('B', row, column, color, Type::BISHOP)
{ }


// PieceInterface implemented methods
void Bishop::Move(Position destination, Matrix& board)
{

}

bool Bishop::IsValid(Position destination, const Matrix& board) const
{
    return false;
}

PositionList Bishop::CreatePattern(const Matrix& board) const
{
    return PositionList();
}


#include "Queen.h"

// Constructor
Queen::Queen(int row, int column, Color color) 
    : Piece('Q', row, column, color, Type::QUEEN)
{ }


// PieceInterface implemented methods
void Queen::Move(Position destination, Matrix& board)
{

}

bool Queen::IsValid(Position destination, const Matrix& board) const
{
    return false;
}

PositionList Queen::CreatePattern(const Matrix& board) const
{
    return PositionList();
}


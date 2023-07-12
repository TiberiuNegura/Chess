#include "Queen.h"

Queen::Queen(int row, int column, Color color) 
    : Piece('Q', row, column, color, Type::QUEEN)
{

}

void Queen::move(Position destination, Matrix& board)
{
}

bool Queen::isValid(Position destination, const Matrix& board)
{
    return false;
}

PositionList Queen::createPattern(const Matrix& board)
{
    return PositionList();
}


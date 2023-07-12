#include "Bishop.h"


Bishop::Bishop(
    int row,
    int column,
    Color color
) : Piece('B', row, column, color, Type::BISHOP)
{
}

void Bishop::move(Position destination, Matrix& board)
{
}

bool Bishop::isValid(Position destination, const Matrix& board)
{
    return false;
}

PositionList Bishop::createPattern(const Matrix& board)
{
    return PositionList();
}


#include "Bishop.h"


Bishop::Bishop(
    int row,
    int column,
    Color color
) : Piece('B', row, column, color, Type::BISHOP)
{
}

void Bishop::move(std::pair<int, int> destination, std::array<std::array<PiecePtr, 8>, 8>& board)
{
}

bool Bishop::isValid(std::pair<int, int> destination, const std::array<std::array<PiecePtr, 8>, 8>& board)
{
    return false;
}

std::vector<std::pair<int, int>> Bishop::createPattern(const std::array<std::array<PiecePtr, 8>, 8>& board)
{
    return std::vector<std::pair<int, int>>();
}


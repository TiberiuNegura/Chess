#include "Queen.h"

Queen::Queen(int row, int column, Color color) 
    : Piece('Q', row, column, color, Type::QUEEN)
{

}

void Queen::move(std::pair<int, int> destination, std::array<std::array<PiecePtr, 8>, 8>& board)
{
}

bool Queen::isValid(std::pair<int, int> destination, const std::array<std::array<PiecePtr, 8>, 8>& board)
{
    return false;
}

std::vector<std::pair<int, int>> Queen::createPattern(const std::array<std::array<PiecePtr, 8>, 8>& board)
{
    return std::vector<std::pair<int, int>>();
}


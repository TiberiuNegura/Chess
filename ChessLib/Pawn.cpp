#include "Pawn.h"



Pawn::Pawn(
    int row,
    int column,
    Color color
) : Piece('P', row, column, color, Type::PAWN)
{

}

void Pawn::move(std::pair<int, int> destination, std::array<std::array<PiecePtr, 8>, 8>& board)
{
}

bool Pawn::isValid(std::pair<int, int> destination, const std::array<std::array<PiecePtr, 8>, 8>& board)
{
    return false;
}

std::vector<std::pair<int, int>> Pawn::createPattern(const std::array<std::array<PiecePtr, 8>, 8>& board)
{
    return std::vector<std::pair<int, int>>();
}

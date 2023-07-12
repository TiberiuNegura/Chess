#include "Pawn.h"



Pawn::Pawn(
    int row,
    int column,
    Color color
) : Piece('P', row, column, color, Type::PAWN)
{

}

void Pawn::move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces)
{
}

bool Pawn::isValid(std::pair<int, int> destination)
{
    return false;
}

std::vector<std::pair<int, int>> Pawn::createPattern()
{
    throw std::logic_error("The method or operation is not implemented.");
}

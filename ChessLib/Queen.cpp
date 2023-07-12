#include "Queen.h"

Queen::Queen(int row, int column, Color color) 
    : Piece('Q', row, column, color, Type::QUEEN)
{

}

void Queen::move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces)
{
}

bool Queen::isValid(std::pair<int, int> destination)
{
    return false;
}

std::vector<std::pair<int, int>> Queen::createPattern()
{
    throw std::logic_error("The method or operation is not implemented.")  ;
}

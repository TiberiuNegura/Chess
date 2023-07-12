#include "Rook.h"

Rook::Rook(
	int row,
	int column,
	Color color
) : Piece('R', row, column, color, Type::ROOK)
{

}

void Rook::move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces)
{
	
}

bool Rook::isValid(std::pair<int, int> destination)
{
	return true;
}

std::vector<std::pair<int, int>> Rook::createPattern()
{
	throw std::logic_error("The method or operation is not implemented.");
}

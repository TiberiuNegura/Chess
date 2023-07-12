#include "King.h"



King::King(
	int row,
	int column,
	Color color
) : Piece('K', row, column, color, Type::KING)
{
}

void King::move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool King::isValid(std::pair<int, int> destination)
{
	throw std::logic_error("The method or operation is not implemented.");
}

std::vector<std::pair<int, int>> King::createPattern()
{
	throw std::logic_error("The method or operation is not implemented.");
}

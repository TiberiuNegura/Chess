#include "Horse.h"


Horse::Horse(
	int row,
	int column,
	Color color
) : Piece('H', row, column, color, Type::HORSE)
{
}

void Horse::move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces)
{
	
}

bool Horse::isValid(std::pair<int, int> destination)
{
	return true;
}

std::unordered_set<std::pair<int, int>> Horse::createPattern()
{
	throw std::logic_error("The method or operation is not implemented.");
}

#include "Horse.h"


Horse::Horse(
	int row,
	int column,
	Color color
) : Piece('H', row, column, color, Type::HORSE)
{
}

void Horse::move(std::pair<int, int> destination, std::array<std::array<PiecePtr, 8>, 8>& board)
{
}

bool Horse::isValid(std::pair<int, int> destination, const std::array<std::array<PiecePtr, 8>, 8>& board)
{
	return false;
}

std::vector<std::pair<int, int>> Horse::createPattern(const std::array<std::array<PiecePtr, 8>, 8>& board)
{
	return std::vector<std::pair<int, int>>();
}



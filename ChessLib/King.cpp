#include "King.h"



King::King(
	int row,
	int column,
	Color color
) : Piece('K', row, column, color, Type::KING)
{
}

void King::move(std::pair<int, int> destination, std::array<std::array<PiecePtr, 8>, 8>& board)
{
}

bool King::isValid(std::pair<int, int> destination, const std::array<std::array<PiecePtr, 8>, 8>& board)
{
	return false;
}

std::vector<std::pair<int, int>> King::createPattern(const std::array<std::array<PiecePtr, 8>, 8>& board)
{
	return std::vector<std::pair<int, int>>();
}


#include "Rook.h"

Rook::Rook(
	int row,
	int column,
	Color color
) : Piece('R', row, column, color, Type::ROOK)
{

}

void Rook::move(std::pair<int, int> destination, std::array<std::array<PiecePtr, 8>, 8>& board)
{
}

bool Rook::isValid(std::pair<int, int> destination, const std::array<std::array<PiecePtr, 8>, 8>& board)
{
	return false;
}

std::vector<std::pair<int, int>> Rook::createPattern(const std::array<std::array<PiecePtr, 8>, 8>& board)
{
	return std::vector<std::pair<int, int>>();
}


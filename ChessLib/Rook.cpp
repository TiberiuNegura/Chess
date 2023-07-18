#include "Rook.h"

// Constructor
Rook::Rook(
	int row,
	int column,
	EColor color
) : Piece('R', row, column, color, EType::ROOK)
{ }

std::vector<PositionList> Rook::CreatePattern() const
{
	PositionList positionsLeft, positionsRight, positionsUp, positionsDown;
	int row = m_position.first, column = m_position.second;
	for (int index = column-1; index >= 0; index--)
		positionsLeft.emplace_back(row, index);
	for (int index = column+1; index < 8; index++)
		positionsRight.emplace_back(row, index);
	for (int index = row-1; index >= 0; index--)
		positionsUp.emplace_back(index, column);
	for (int index = row+1; index < 8; index++)
		positionsDown.emplace_back(index, column);
	return {
		positionsLeft,
		positionsRight,
		positionsUp,
		positionsDown
	};
}


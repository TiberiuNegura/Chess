#include "Rook.h"

// Constructor
Rook::Rook(
	int row,
	int column,
	Color color
) : Piece('R', row, column, color, Type::ROOK)
{ }

std::vector<PositionList> Rook::CreatePattern() const
{
	PositionList positionsLeft, positionsRight, positionsUp, positionsDown;
	int row = m_position.first, column = m_position.second;
	for (int index = column; index >= 0; index--)
		positionsLeft.emplace_back(row, index);
	for (int index = column; index < 8; index++)
		positionsRight.emplace_back(row, index);
	for (int index = row; index >= 0; row--)
		positionsUp.emplace_back(index, column);
	for (int index = row; index < 8; row++)
		positionsDown.emplace_back(index, column);
	return {
		positionsLeft,
		positionsRight,
		positionsUp,
		positionsDown
	};
}


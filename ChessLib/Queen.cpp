#include "Queen.h"

// Constructor
Queen::Queen(
	int row,
	int column,
	Color color
): Piece('Q', row, column, color, Type::QUEEN)
{ }

std::vector<PositionList> Queen::CreatePattern() const
{
	// this is soon to be refactored, it`s just a try
	PositionList leftDown, leftUp, rightDown, rightUp, positionsLeft, positionsRight, positionsUp, positionsDown;
	int row = m_position.first, column = m_position.second;
	// bishop code
	for (int index = 1; column - index >= 0 && row - index >= 0; index++)
		leftUp.emplace_back(row - index, column - index);
	for (int index = 1; column - index >= 0 && row + index < 8; index++)
		leftDown.emplace_back(row + index, column - index);
	for (int index = 1; column + index < 8 && row + index < 8; index++)
		rightDown.emplace_back(row + index, column + index);
	for (int index = 1; column + index < 8 && row - index >= 0; index++)
		rightUp.emplace_back(row - index, column + index);
	// rook code
	for (int index = column; index >= 0; index--)
		positionsLeft.emplace_back(row, index);
	for (int index = column; index < 8; index++)
		positionsRight.emplace_back(row, index);
	for (int index = row; index >= 0; row--)
		positionsUp.emplace_back(index, column);
	for (int index = row; index < 8; row++)
		positionsDown.emplace_back(index, column);
	return {
		leftUp,
		leftDown,
		rightDown,
		rightUp,
		positionsLeft,
		positionsRight,
		positionsUp,
		positionsDown
	};
}



#include "Bishop.h"

// Constructor
Bishop::Bishop(
	int row,
	int column,
	Color color
) : Piece('B', row, column, color, Type::BISHOP)
{ }

std::vector<PositionList> Bishop::CreatePattern() const
{
	PositionList leftDown, leftUp, rightDown, rightUp; //diagonal path to board corners
	int row = m_position.first, column = m_position.second;

	for (int index = 1; column - index >= 0 && row - index >= 0; index++)
		leftUp.emplace_back(row - index, column - index);
	for (int index = 1; column - index >= 0 && row + index < 8; index++)
		leftDown.emplace_back(row + index, column - index);
	for (int index = 1; column + index < 8 && row + index < 8; index++)
		rightDown.emplace_back(row + index, column + index);
	for (int index = 1; column + index < 8 && row - index >= 0; index++)
		rightUp.emplace_back(row - index, column + index);
	return {
		leftUp,
		leftDown,
		rightDown,
		rightUp
	};
}



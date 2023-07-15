#include "King.h"

// Constructor
King::King(
	int row,
	int column,
	Color color
) : Piece('K', row, column, color, Type::KING)
{ }

std::vector<PositionList> King::CreatePattern() const
{
	PositionList positions;
	int row = m_position.first, column = m_position.second;
	for (int rowIndex = row - 1; rowIndex <= row + 1; rowIndex++)
		for (int columnIndex = column - 1; columnIndex <= column + 1; columnIndex++)
			if (rowIndex != row || columnIndex != column) // skip piece current position
				positions.emplace_back(rowIndex, columnIndex);

	return {positions};
}


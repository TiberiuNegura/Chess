#include "King.h"

// Constructor
King::King(EColor color) 
	: Piece('K', color, EType::KING)
{ 

}

std::vector<PositionList> King::GetDirections(Position pos) const
{
	PositionList positions;
	int row = pos.first, column = pos.second;
	for (int rowIndex = row - 1; rowIndex <= row + 1; rowIndex++)
		for (int columnIndex = column - 1; columnIndex <= column + 1; columnIndex++)
			if (rowIndex != row || columnIndex != column) // skip piece current position
				positions.emplace_back(rowIndex, columnIndex);

	return {positions};
}


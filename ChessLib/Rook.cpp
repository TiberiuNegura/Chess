#include "Rook.h"

// Constructor
Rook::Rook(EColor color) 
	: Piece('R', color, EType::ROOK)
{

}

Directions Rook::GetDirections(Position pos) const
{
	PositionList positionsLeft, positionsRight, positionsUp, positionsDown;
	int row = pos.first, column = pos.second;
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

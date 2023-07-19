#include "Bishop.h"

// Constructor
Bishop::Bishop(EColor color ) 
	: Piece('B', color, EType::BISHOP)
{

}

std::vector<PositionList> Bishop::GetDirections(Position pos) const
{
	PositionList leftDown, leftUp, rightDown, rightUp; //diagonal path to board corners
	int row = pos.first, column = pos.second;

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

PiecePtr Bishop::Produce(EColor color)
{
	return std::make_shared<Bishop>(color);
}



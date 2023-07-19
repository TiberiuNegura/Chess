#include "Pawn.h"

// Constructor
Pawn::Pawn(EColor color) 
	: Piece('P', color, EType::PAWN)
{ 

}

std::vector<PositionList> Pawn::GetDirections(Position pos) const
{
	PositionList positions;
	int row = pos.first, column = pos.second;
	int nextPos = (m_color == EColor::WHITE) ? -1 : 1;
	positions.emplace_back(row + nextPos, column);
	if (m_color == EColor::WHITE && row == 6 || m_color == EColor::BLACK && row == 1)
		positions.emplace_back(row + 2 * nextPos, column);
	positions.emplace_back(row + nextPos, column + 1);
	positions.emplace_back(row + nextPos, column - 1);
	return {positions};
}

PiecePtr Pawn::Produce(EColor color)
{
	return std::make_shared<Pawn>(color);
}

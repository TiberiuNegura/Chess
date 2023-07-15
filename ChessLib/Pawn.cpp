#include "Pawn.h"

// Constructor
Pawn::Pawn(
	int row,
	int column,
	Color color
) : Piece('P', row, column, color, Type::PAWN), isFirstMove(true)
{ }

std::vector<PositionList> Pawn::CreatePattern() const
{
	PositionList positions;
	int row = m_position.first, column = m_position.second;
	int nextPos = (m_color == Color::WHITE) ? -1 : 1;
	positions.emplace_back(row + nextPos, column);
	if (isFirstMove)
		positions.emplace_back(row + 2 * nextPos, column);
	positions.emplace_back(row + nextPos, column + 1);
	positions.emplace_back(row + nextPos, column - 1);
	return {positions};
}

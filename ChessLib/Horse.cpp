#include "Horse.h"

// Constructor
Horse::Horse(
	int row,
	int column,
	Color color
) : Piece('H', row, column, color, Type::HORSE)
{ }


std::vector<PositionList> Horse::CreatePattern() const
{
	PositionList positions;
	int row = m_position.first, column = m_position.second;
	for (int index = 0; index < 4; index++)
	{
		Position pos = { row + pow(-1, index/2), row + 2 * pow(-1, index%2)};
		// the above formula generates coordinates (+- 1 +-2)
		positions.emplace_back(pos.first, pos.second);
		positions.emplace_back(pos.second, pos.first); // inverted coordinates for complete movement set
	}
	return { positions };
}


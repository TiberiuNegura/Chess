#include "Horse.h"

// Constructor
Horse::Horse(
	int row,
	int column,
	EColor color
) : Piece('H', row, column, color, EType::HORSE)
{ }


std::vector<PositionList> Horse::GetDirections() const
{
	PositionList positions;
	int row = m_position.first, column = m_position.second;
	for (int index = 0; index < 4; index++)
	{
		Position pos1 = { row + pow(-1, index/2), column + 2 * pow(-1, index%2)};
		Position pos2 = { row + 2 * pow(-1, index/2), column + pow(-1, index%2)};
		// the above formula generates coordinates (+- 1 +-2)
		positions.emplace_back(pos1);
		positions.emplace_back(pos2); // inverted coordinates for complete movement set
	}

	//for (auto& it : positions)
	//	std::cout << it.first << " " << it.second << std::endl;
	return { positions };
}


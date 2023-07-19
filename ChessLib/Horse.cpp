#include "Horse.h"

// Constructor
Horse::Horse(EColor color)
	: Piece('H', color, EType::HORSE)
{ 

}


std::vector<PositionList> Horse::GetDirections(Position pos) const
{
	PositionList positions;
	int row = pos.first, column = pos.second;
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

PiecePtr Horse::Produce(EColor color)
{
	return std::make_shared<Horse>(color);
}
#pragma once
#include "PositionInterface.h"

class Position : public PositionInterface
{
public:
	// Constructor
	Position(char row, char column);


	// Getters
	char getRow() const override;
	char getColumn() const override;

	std::pair<int, int> getMatrixPos() const override;

	static std::pair<char, char> getTablePos(int row, int column);

	struct comparator {
		int operator()(const std::pair<char, char>& x) const
		{
			return (int)x.first + (int)x.second;
		}
	};
private:
	char row, column;
};


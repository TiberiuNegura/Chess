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

private:
	char row, column;
};


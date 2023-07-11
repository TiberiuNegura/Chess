#pragma once
#include "PositionInterface.h"

class Position : public PositionInterface
{
public:
	// Constructor
	Position(char row, char column)
		: row(row)
		, column(column)
	{ }


	// Getters
	char getRow() const override
	{
		return this->row;
	}
	char getColumn() const override
	{
		return this->column;
	}

	std::pair<int, int> getMatrixPos() const override
	{
		return { getRow() - '0', getColumn() - 'A' };
	}

	static std::pair<char, char> getTablePos(int row, int column)
	{
		return { row - '0' , column - 'A' };
	}

private:
	char row, column;
};


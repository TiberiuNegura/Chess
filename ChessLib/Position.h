#pragma once

#include <tuple>

class Position
{
public:
	// Constructor
	Position(char row, char column)
		: row(row)
		, column(column)
	{ }


	// Getters
	char getRow() const
	{
		return this->row;
	}
	char getColumn() const
	{
		return this->column;
	}

	std::pair<int, int> getMatrixPos() const
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


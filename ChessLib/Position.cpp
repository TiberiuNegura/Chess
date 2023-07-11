#include "Position.h"

Position::Position(char row, char column) : row(row)
, column(column)
{

}

char Position::getRow() const
{
	return this->row;
}

char Position::getColumn() const
{
	return this->column;
}

std::pair<int, int> Position::getMatrixPos() const
{
	return { getRow() - '0', getColumn() - 'A' };
}

std::pair<char, char> Position::getTablePos(int row, int column)
{
	return { row - '0' , column - 'A' };
}

#include "Horse.h"

// Constructor
Horse::Horse(
	int row,
	int column,
	Color color
) : Piece('H', row, column, color, Type::HORSE)
{ }

// PieceInterface implemented methods
void Horse::Move(Position destination, Matrix& board)
{

}

bool Horse::IsValid(Position destination, const Matrix& board) const
{
	return false;
}

PositionList Horse::CreatePattern(const Matrix& board) const
{
	PositionList positions;
	int row = m_position.first, column = m_position.second;

	for (int index = 0; index < 4; index++) 
	{
		// TODO: add a method to return the color of a piece at position...
		Position pos = { row + index % 4, row + index / 4 };
		if (!Piece::IsOutOfBounds(pos.first, pos.second))
			positions.emplace_back(pos.first, pos.second);
		if (!Piece::IsOutOfBounds(pos.second, pos.first))
			positions.emplace_back(pos.second, pos.first);
	}
}



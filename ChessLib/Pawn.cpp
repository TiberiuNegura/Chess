#include "Pawn.h"
Pawn::Pawn(
	int row,
	int column,
	Color color
) : Piece('P', row, column, color, Type::PAWN)
{
	isFirstMove = true;
}

void Pawn::move(Position destination, Matrix& board)
{
	// if can move, don't forget to disable isFirstMove
}

bool Pawn::isValid(Position destination, const Matrix& board)
{
	return false;
}

PositionList Pawn::createPattern(const Matrix& board)
{
	PositionList positions;
	int row = m_position.first, column = m_position.second;
	int nextPos = (m_color == Color::WHITE) ? -1 : 1;


	if (auto elem = board[row + nextPos][column])
		{
			auto type = elem->getType();
			auto pos = elem->getPosition();
			positions.emplace_back(pos);
			if (isFirstMove)
			{
				if (auto elem2 = board[pos.first + nextPos][pos.second])
				{
					auto type2 = elem2->getType();
					auto pos2 = elem->getPosition();
					positions.emplace_back(pos2);

				}
			}
		}
		
	if (auto elem = board[row + nextPos][column - 1])
	{
		auto color = elem->getColor();
	}
		if(board[row -1][column -1]->getColor() == Color::BLACK) {
			positions.emplace_back(board[row - 1][column - 1]->getPosition());
		}
		if (board[row - 1][column + 1]->getColor() == Color::BLACK) {
			positions.emplace_back(board[row - 1][column + 1]->getPosition());
		}
	return positions;
}

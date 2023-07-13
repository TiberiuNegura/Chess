#include "Pawn.h"
Pawn::Pawn(
	int row,
	int column,
	Color color
) : Piece('P', row, column, color, Type::PAWN)
  , isFirstMove(true)
{
}

void Pawn::move(Position destination, Matrix& board)
{
	if (!isValid(destination, board))
		throw std::exception("Not a valid move!");
	board[destination.first][destination.second] = board[m_position.first][m_position.second];
	board[m_position.first][m_position.second] = nullptr;
	m_position = destination;
	if (isFirstMove)
		isFirstMove = false;

	
	// if can move, don't forget to disable isFirstMove
}

bool Pawn::isValid(Position destination, const Matrix& board)
{
	PositionList positions = createPattern(board);
	for (auto& pos : positions) 
	{
		if (destination == pos)
			return true;
	}
	return false;
}

PositionList Pawn::createPattern(const Matrix& board)
{
	PositionList positions;
	int row = m_position.first, column = m_position.second;
	int nextPos = (m_color == Color::WHITE) ? -1 : 1;

	if (!Piece::IsOutOfBounds(row + nextPos, column))
	{
		auto elem = board[row + nextPos][column];
		if (!elem)
		{
			Position pos = { row + nextPos, column };
			positions.emplace_back(pos);
			if (!Piece::IsOutOfBounds(pos.first + nextPos, pos.second))
			{
				auto elem = board[pos.first + nextPos][pos.second];
				if (isFirstMove && !elem)
					positions.emplace_back(pos);
			}
		}
	}

	for (int sign = 0; sign < 2; sign++)
	{
		if (!Piece::IsOutOfBounds(row + nextPos, column + pow(-1, sign))) 
		{
			auto elem = board[row + nextPos][column + pow(-1, sign)];
			if (elem && elem->getColor() != getColor())
			{
				Position pos = { row + nextPos, column + pow(-1, sign) };
				positions.emplace_back(pos);
			}
		}
	}


	return positions;
}

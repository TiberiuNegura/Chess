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
	//int first, second;
	/*if (this->m_color == Color::WHITE) {
		first = m_position.first;
		second = m_position.second;
	}
	else if (this->m_color == Color::BLACK) {
		first = 8 - m_position.first;
		second = 8 - m_position.second;
	}*/
	long row = m_position.first, column = m_position.second;
	if (this->m_color == Color::WHITE) {
		if(board[row-1][column]->getType() == Type::EMPTY) {
			positions.emplace_back(board[row - 1][column]->getPosition());
			if (this->isFirstMove && board[row - 2][column]->getType() == Type::EMPTY) {
				positions.emplace_back(board[row - 2][column]->getPosition());
			}
		}
		if(board[row -1][column -1]->getColor() == Color::BLACK) {
			positions.emplace_back(board[row - 1][column - 1]->getPosition());
		}
		if (board[row - 1][column + 1]->getColor() == Color::BLACK) {
			positions.emplace_back(board[row - 1][column + 1]->getPosition());
		}
	}
	else if (m_color == Color::BLACK) {
		if (board[row + 1][column]->getType() == Type::EMPTY) {
			positions.emplace_back(board[row + 1][column]->getPosition());
			if (this->isFirstMove && board[row + 2][column]->getType() == Type::EMPTY) {
				positions.emplace_back(board[row + 2][column]->getPosition());
			}
		}
		if (board[row + 1][column + 1]->getColor() == Color::WHITE) {
			positions.emplace_back(board[row + 1][column + 1]->getPosition());
		}
		if (board[m_position.first + 1][column - 1]->getColor() == Color::WHITE) {
			positions.emplace_back(board[row +1][column - 1]->getPosition());
		}
	}
	return positions;
}

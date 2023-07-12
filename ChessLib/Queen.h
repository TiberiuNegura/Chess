#pragma once
#include "Piece.h"
class Queen : public Piece
{
	public:
		Queen(int row = 0, int column = 0, Color color = Color::NONE);

		

		// Inherited via Piece
		virtual void move(Position destination, Matrix& board) override;

		virtual bool isValid(Position destination, const Matrix& board) override;

		virtual PositionList createPattern(const Matrix& board) override;

};


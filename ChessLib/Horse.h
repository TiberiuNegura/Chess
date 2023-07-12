#pragma once

#include "Piece.h"

class Horse : public Piece
{
	public:
		Horse(
			int row = 0,
			int column = 0,
			Color color = Color::NONE
		);

		


		// Inherited via Piece
		virtual void move(Position destination, Matrix& board) override;

		virtual bool isValid(Position destination, const Matrix& board) override;

		virtual PositionList createPattern(const Matrix& board) override;

};


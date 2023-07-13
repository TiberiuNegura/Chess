#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	// Constructor
	Bishop(
		int row = 0,
		int column = 0,
		Color color = Color::NONE
	);

	// PieceInterface implemented methods
	virtual void Move(Position destination, Matrix& board) override;
	virtual bool IsValid(Position destination, const Matrix& board) const override;
	virtual PositionList CreatePattern(const Matrix& board) const override;

};


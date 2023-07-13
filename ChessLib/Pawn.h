#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	// Constructor
	Pawn(
		int row = 0,
		int column = 0,
		Color color = Color::NONE
	);
		
	// PieceInterface implemented methods
	virtual void Move(Position destination, Matrix& board) override;
	virtual bool IsValid(Position destination, const Matrix& board) const override;
	virtual PositionList CreatePattern(const Matrix& board) const override;
private:
	bool isFirstMove;
};

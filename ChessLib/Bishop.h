#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	// Constructor
	Bishop(EColor color = EColor::NONE);

	// Inherited via Piece
	std::vector<PositionList> GetDirections(Position pos) const override;

	static PiecePtr Produce(EColor color);

};


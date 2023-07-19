#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	// Constructor
	Pawn(EColor color = EColor::NONE);

	// Inherited via Piece
	std::vector<PositionList> GetDirections(Position pos) const override;
};

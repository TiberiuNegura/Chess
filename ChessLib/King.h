#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	// Constructor
	King(EColor color = EColor::NONE);

	

	// Inherited via Piece
	std::vector<PositionList> GetDirections(Position pos) const override;

};


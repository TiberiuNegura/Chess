#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	// Constructor
	King(EColor color = EColor::NONE);

	

	// Inherited via Piece
	Directions GetDirections(Position pos) const override;


};


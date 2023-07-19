#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	// Constructor
	Queen(EColor color = EColor::NONE);

	

	// Inherited via Piece
	Directions GetDirections(Position pos) const override;


};


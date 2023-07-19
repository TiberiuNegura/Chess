#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	// Constructor
	Rook(EColor color = EColor::NONE);

	

	// Inherited via Piece
	Directions GetDirections(Position pos) const override;


};


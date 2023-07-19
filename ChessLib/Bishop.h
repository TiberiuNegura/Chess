#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	// Constructor
	Bishop(EColor color = EColor::NONE);

	// Inherited via Piece
	Directions GetDirections(Position pos) const override;


};


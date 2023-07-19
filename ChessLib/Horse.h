#pragma once

#include "Piece.h"

class Horse : public Piece
{
public:
	// Constructor
	Horse(EColor color = EColor::NONE);

	

	Directions GetDirections(Position pos) const override;


};


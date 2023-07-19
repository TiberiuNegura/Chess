#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	// Constructor
	Pawn(EColor color = EColor::NONE);

	// Inherited via Piece
	Directions GetDirections(Position pos) const override;

};

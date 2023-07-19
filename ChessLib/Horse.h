#pragma once

#include "Piece.h"

class Horse : public Piece
{
public:
	// Constructor
	Horse(EColor color = EColor::NONE);

	

	std::vector<PositionList> GetDirections(Position pos) const override;

};


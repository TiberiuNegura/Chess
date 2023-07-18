#pragma once

#include "Piece.h"

class Horse : public Piece
{
public:
	// Constructor
	Horse(
		int row = 0,
		int column = 0,
		EColor color = EColor::NONE
	);

	

	std::vector<PositionList> GetDirections() const override;

};


#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	// Constructor
	Queen(
		int row = 0,
		int column = 0,
		EColor color = EColor::NONE
	);

	

	// Inherited via Piece
	std::vector<PositionList> GetDirections() const override;

};


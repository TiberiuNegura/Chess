#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	// Constructor
	King(
		int row = 0,
		int column = 0,
		EColor color = EColor::NONE
	);

	

	// Inherited via Piece
	std::vector<PositionList> CreatePattern() const override;

};


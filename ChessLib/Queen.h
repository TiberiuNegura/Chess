#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	// Constructor
	Queen(
		int row = 0,
		int column = 0,
		Color color = Color::NONE
	);

	

	// Inherited via Piece
	std::vector<PositionList> CreatePattern() const override;

};


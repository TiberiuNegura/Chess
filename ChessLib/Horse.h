#pragma once

#include "Piece.h"

class Horse : public Piece
{
public:
	// Constructor
	Horse(
		int row = 0,
		int column = 0,
		Color color = Color::NONE
	);

	

	std::vector<PositionList> CreatePattern() const override;

};


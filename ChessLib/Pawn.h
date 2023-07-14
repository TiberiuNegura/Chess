#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	// Constructor
	Pawn(
		int row = 0,
		int column = 0,
		Color color = Color::NONE
	);
		
	
private:
	bool isFirstMove;

	// Inherited via Piece
	std::vector<PositionList> CreatePattern() const override;
};

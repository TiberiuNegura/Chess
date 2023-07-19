#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	// Constructor
	Queen(EColor color = EColor::NONE);

	

	// Inherited via Piece
	std::vector<PositionList> GetDirections(Position pos) const override;

	static PiecePtr Produce(EColor color);

};


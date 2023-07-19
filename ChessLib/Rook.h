#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	// Constructor
	Rook(EColor color = EColor::NONE);

	

	// Inherited via Piece
	std::vector<PositionList> GetDirections(Position pos) const override;

	static PiecePtr Produce(EColor color);

};


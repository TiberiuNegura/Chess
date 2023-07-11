#pragma once

#include "PieceInterface.h"

class Piece : public PieceInterface
{

	public:
		void move(Position position) override;
		bool isValid(Position position) override;
		std::unordered_set<Position, Position::comparator> createPattern() override;



};


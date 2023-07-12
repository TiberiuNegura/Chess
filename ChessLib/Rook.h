#pragma once

#include "Piece.h"

class Rook : public Piece
{
	
	public:
		Rook();
		void move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces) override;
		bool isValid(std::pair<int, int> destination) override;


		std::unordered_set<std::pair<int, int>> createPattern() override;

};


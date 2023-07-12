#pragma once

#include "Piece.h"

class Rook : public Piece
{
	
	public:
		Rook(int row = 0, int column = 0, Color color = Color::NONE)
			: Piece('R', row, column, color, Type::ROOK)
		{ }
		void move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces) override;
		bool isValid(std::pair<int, int> destination) override;


		std::unordered_set<std::pair<int, int>> createPattern() override;

};


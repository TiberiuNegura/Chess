#pragma once

#include "Piece.h"

class Horse : public Piece
{
	public:
		Horse(
			int row = 0,
			int column = 0,
			Color color = Color::NONE
		);

		void move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces) override;
		bool isValid(std::pair<int, int> destination) override;

		std::unordered_set<std::pair<int, int>> createPattern() override;

};


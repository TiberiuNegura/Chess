#pragma once
#include "Piece.h"
class Bishop : public Piece
{
	public:
		Bishop(
			int row = 0,
			int column = 0,
			Color color = Color::NONE
		);
		~Bishop() = default;

		// Inherited via PieceInterface
		virtual void move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces) override;
		virtual bool isValid(std::pair<int, int> destination) override;
		virtual std::unordered_set<std::pair<int, int>> createPattern() override;
};


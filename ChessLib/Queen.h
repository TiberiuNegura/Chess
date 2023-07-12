#pragma once
#include "Piece.h"
class Queen : public Piece
{
	public:
		Queen();
		~Queen() = default;

		// Inherited via PieceInterface
		virtual void move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces) override;
		virtual bool isValid(std::pair<int, int> destination) override;
		virtual std::unordered_set<std::pair<int, int>> createPattern() override;
};


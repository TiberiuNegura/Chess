#pragma once

#include "Piece.h"

class King : public Piece
{

	public:
		King(
			int row = 0,
			int column = 0,
			Color color = Color::NONE
		);

		


		// Inherited via Piece
		virtual void move(std::pair<int, int> destination, std::array<std::array<PiecePtr, 8>, 8>& board) override;

		virtual bool isValid(std::pair<int, int> destination, const std::array<std::array<PiecePtr, 8>, 8>& board) override;

		virtual std::vector<std::pair<int, int>> createPattern(const std::array<std::array<PiecePtr, 8>, 8>& board) override;

};


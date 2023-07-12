#pragma once
#include <memory>
#include <array>
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Horse.h"
#include "Queen.h"
#include "King.h"

using PiecePtr = std::shared_ptr<Piece>;

class Game
{
	public:
		Game();
		PiecePtr getElement(int row, int column);
	private:
		std::array<std::array<PiecePtr, 8>, 8> m_board;
};


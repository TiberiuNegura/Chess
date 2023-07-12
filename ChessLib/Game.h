#pragma once
#include <memory>
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Horse.h"
#include "Queen.h"
#include "King.h"


class Game
{
	public:
		Game();
		PiecePtr getElement(int row, int column);
		std::array<std::array<PiecePtr, 8>, 8> GetGameboard();
	private:
		Matrix m_board;
};


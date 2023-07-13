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
	// Constructor
	Game();

	// Getters
	PiecePtr GetElement(int row, int column);
	Matrix& GetGameboard();

private:
	Matrix m_board;
};


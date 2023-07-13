#pragma once

#include "IPiece.h"

class IBoard
{
public:
	virtual Matrix& GetGameBoard() = 0;
	virtual void MoveOnBoard(Position start, Position destination) = 0;

	~IBoard() = default;
};


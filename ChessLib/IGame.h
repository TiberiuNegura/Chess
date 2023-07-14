#pragma once

#include "IBoard.h"

class IGame
{
public:
	virtual void StartGame() = 0;
	virtual bool IsCheck() = 0;
	virtual bool IsCheckmate() = 0;
	virtual void MovePiece(Position start, Position destination) = 0;
	virtual Matrix& GetBoard() = 0;

	~IGame() = default;
};


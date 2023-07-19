#pragma once

#include "IGame.h"
#include "Board.h"

class Game : public IGame
{
public:
	// Constructor
	Game();

	// IGame methods
	bool IsCheckmate(EColor color) const override;
	void MovePiece(Position start, Position destination) override;
	
	MatrixPtr GetBoard() const override;
	EColor GetTurn() const override;

private:
	Board m_board;
	EColor m_turn;
};


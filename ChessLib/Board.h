#pragma once

#include "IBoard.h"

class Board : public IBoard
{
public:

	Board();

	// Inherited via BoardInterface
	virtual Matrix& GetGameBoard() override;
	virtual void MoveOnBoard(Position start, Position destination) override;

private:
	Matrix m_board;
};


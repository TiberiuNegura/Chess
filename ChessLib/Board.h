#pragma once

#include "IBoard.h"

class Board : public IBoard
{
public:

	Board();

	// Inherited via BoardInterface
	Matrix& GetGameBoard() override;
	void MoveOnBoard(Position start, Position destination) override;
	bool IsValid(Position start, Position end) override;
	PositionList PatternValidation(Position start, std::vector<PositionList> positions);

private:
	Matrix m_board;

	static bool IsOutOfBounds(int row, int column);
};


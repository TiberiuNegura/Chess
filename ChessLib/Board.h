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
	void UpdatePosition(Position start, Position end);
	static bool IsOutOfBounds(int row, int column);

private:
	Matrix m_board;

};


#pragma once

#include "IBoard.h"
#include "IGame.h"

class Board : public IBoard
{
public:

	Board();

	// Inherited via BoardInterface
	const Matrix& GetGameBoard() const override;
	PositionList PatternValidation(Position start, std::vector<PositionList> positions);
	void UpdatePosition(Position start, Position end);
	void RevertPosition(PiecePtr toRevert) override;
	static bool IsOutOfBounds(int row, int column);

private:
	Matrix m_board;

};


#pragma once

#include "IBoard.h"
#include "IGame.h"

class Board : public IBoard
{
public:

	Board();

	// Inherited via BoardInterface
	const Matrix& GetGameBoard() const override;

	bool IsEmpty(Position p) const override;

	PositionList ComputePositionList(Position start, std::vector<PositionList> positions);
	void UpdatePosition(Position start, Position end);
	void RevertPosition(PiecePtr toRevert) override;
	static bool IsOutOfBounds(Position p);

private:
	Matrix m_board;

};


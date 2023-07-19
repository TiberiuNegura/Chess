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

	PositionList ComputePositionList(Position start, std::vector<PositionList> positions) const;
	void UpdatePosition(Position start, Position end);
	void RevertPosition(PiecePtr toRevert, Position pos) override;
	static bool IsOutOfBounds(Position p);

private:
	Matrix m_board;

};


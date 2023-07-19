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

	PiecePtr Get(int i, int j) const override;
	PiecePtr Get(Position pos) const override;

	PositionList ComputePositionList(Position start, std::vector<PositionList> positions) const;
	void MovePiece(Position start, Position end);
	void SetPosition(PiecePtr toRevert, Position pos) override;
	static bool IsOutOfBounds(Position p);

	PiecePtr operator[](Position pos) override;

private:
	Matrix m_board;
};


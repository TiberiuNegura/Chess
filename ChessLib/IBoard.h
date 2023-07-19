#pragma once

#include "Piece.h"

using PiecePtr = std::shared_ptr<class Piece>;
using Matrix = std::array<std::array<PiecePtr, 8>, 8>;


class IBoard
{
public:
	virtual const Matrix& GetGameBoard() const = 0;

	virtual bool IsEmpty(Position p) const = 0;

	virtual PositionList ComputePositionList(Position start, std::vector<PositionList> positions) const = 0 ;
	virtual void RevertPosition(PiecePtr toRevert, Position pos) = 0;
	virtual void UpdatePosition(Position start, Position end) = 0;

	~IBoard() = default;
};

using IBoardPtr = std::shared_ptr<IBoard>;


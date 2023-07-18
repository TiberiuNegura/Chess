#pragma once

#include "InteriorIPiece.h"

using Matrix = std::array<std::array<PiecePtr, 8>, 8>;

class IBoard
{
public:
	virtual const Matrix& GetGameBoard() const = 0;

	virtual PositionList PatternValidation(Position start, std::vector<PositionList> positions) = 0;
	
	virtual void UpdatePosition(Position start, Position end) = 0;
	virtual void RevertPosition(PiecePtr toRevert) = 0;

	~IBoard() = default;
};

using IBoardPtr = std::shared_ptr<IBoard>;


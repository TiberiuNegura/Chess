#pragma once

#include "InteriorIPiece.h"

class IBoard
{
public:
	virtual Matrix& GetGameBoard() = 0;
	virtual void MoveOnBoard(Position start, Position destination) = 0;
	virtual PositionList PatternValidation(Position start, std::vector<PositionList> positions) = 0;
	virtual bool IsValid(Position start, Position end) = 0;
	virtual void UpdatePosition(Position start, Position end) = 0;

	~IBoard() = default;
};


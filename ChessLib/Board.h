#pragma once

#include "IBoard.h"

class Board : public IBoard
{
public:

	Board();

	// Inherited via BoardInterface
	Matrix& GetGameBoard() override;
	void MoveOnBoard(Position start, Position destination) override;
	PositionList PatternValidation(Position start, std::vector<PositionList> positions) override;
	bool IsValid(Position start, Position end) override;

private:
	Matrix m_board;

	PositionList PawnPattern(Position start, std::vector<PositionList> pawnMoves);
	PositionList HorsePattern(Position start, std::vector<PositionList> horseMoves);
	PositionList KingPattern(Position start, std::vector<PositionList> kingMoves);
};


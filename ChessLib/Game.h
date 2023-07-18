#pragma once

#include "IGame.h"
#include "IBoard.h"

class Game : public IGame
{
public:
	// Constructor
	Game();

	// IGame methods
	bool IsCheck(EColor color) const override;
	bool IsCheckmate(EColor color) const override;
	void MovePiece(Position start, Position destination) override;
	
	MatrixPtr GetBoard() const override;
	PositionList GetMoves(Position piecePos) const override;
	EColor GetTurn() const override;

private:
	Position FindKing(EColor color) const;

private:
	IBoardPtr m_board;
	EColor m_turn;
};


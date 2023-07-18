#pragma once

#include "IGame.h"
#include "IBoard.h"

class Game : public IGame
{
public:
	// Constructor
	Game();

	bool IsCheck(Color color) override;
	bool IsCheckmate(Color color) override;
	void MovePiece(Position start, Position destination) override;
	MatrixPtr GetBoard() override;
	PositionList GetPattern(Position piecePos) override;
	bool IsValid(Position start, Position end);
	Color GetTurn() override;

private:
	std::shared_ptr<IBoard> m_board;
	Color m_turn;
	Position FindKing(Color color);
};


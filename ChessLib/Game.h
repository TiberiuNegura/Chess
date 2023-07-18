#pragma once

#include "IGame.h"
#include "IBoard.h"

class Game : public IGame
{
public:
	// Constructor
	Game();


	void StartGame() override;
	bool IsCheck(Color color) override;
	bool IsCheckmate() override;
	void MovePiece(Position start, Position destination) override;

	MatrixPtr GetBoard() override;
	PositionList GetPattern(Position piecePos) override;
private:
	std::shared_ptr<IBoard> m_board;
	Position FindKing(Color color);
};


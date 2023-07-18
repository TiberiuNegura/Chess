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
	bool IsCheckmate(Color color) override;
	void MovePiece(Position start, Position destination) override;
	MatrixPtr GetBoard() override;
	PositionList GetPattern(Position piecePos) override;
	bool IsValid(Position start, Position end);
private:
	std::shared_ptr<IBoard> m_board;
	Position FindKing(Color color);
};


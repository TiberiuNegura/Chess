#pragma once

#include <memory>
#include "IGame.h"

class Game : public IGame
{
public:
	// Constructor
	Game();


	void StartGame() override;
	bool IsCheck() override;
	bool IsCheckmate() override;
	void MovePiece(Position start, Position destination) override;

	Matrix& GetBoard() override;

private:
	std::shared_ptr<IBoard> board;
};


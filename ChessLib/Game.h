#pragma once

#include "IGame.h"
#include "Board.h"

class Game : public IGame
{
public:
	// Constructor
	Game();
	Game(std::array<std::array<char, 8>, 8> mat, EColor turn);

	// IGame methods
	void MovePiece(Position start, Position destination) override;
	void MakeCastling(std::string where) override;
	void ChangeTurn();
	
	MatrixPtr GetBoard() const override;
	EColor GetTurn() const override;
	PositionList GetMoves(Position piecePos) const override;

	bool IsGameOver() const override;



private:
	Board m_board;
	EColor m_turn;
};


#pragma once

#include "IGame.h"
#include "Board.h"

enum class EGameState
{
	Playing,
	TieRequest,
	Tie,
	PawnEvolving,
	BlackWon,
	WhiteWon,
};

class Game : public IGame
{
public:
	// Constructor
	Game();
	Game(std::array<std::array<char, 8>, 8> mat, EColor turn);

	void MovePiece(Position start, Position destination) override;
	void MakeCastling(std::string where) override;
	void UpdateTurn();
	void UpdateState(EGameState state);

	// Getters
	MatrixPtr GetBoard() const override;
	EColor GetTurn() const override;
	EGameState GetState() const;
	PositionList GetMoves(Position piecePos) const override;
	
	// tie invitation
	void MakeTieRequest() override;
	bool IsTieRequest() const override;
	void TieRequestResponse(bool answer) override;

	// pawn evolve
	bool IsPawnEvolving() const override;
	void EvolvePawn(char pieceName) override;

	// game over states
	bool IsTie() const override;
	bool BlackWon() const override;
	bool WhiteWon() const override;
	bool IsGameOver() const override;



private:
	Board m_board;
	EColor m_turn;
	EGameState m_state;
};


#pragma once

#include "IGame.h"
#include "Board.h"
#include "IGameListener.h"

enum class EGameState
{
	Playing,
	TieRequest,
	Tie,
	PawnEvolving,
	BlackWon,
	WhiteWon,
	Check
};

enum class Response
{
	CHECK,
	PAWN_UPGRADE,
	TIE_REQUEST,
	WHITE_WON,
	BLACK_WON,
	TIE,
	RESTART
};

class Game : public IGame
{
public:
	// Constructor
	Game();
	Game(CharBoardRepresentation mat, EColor turn, EGameState state);
	Game(const std::string& FenString);

	void MovePiece(Position start, Position destination) override;
	void UpdateTurn();
	void UpdateState(EGameState state);

	// Getters
	MatrixPtr GetBoard() const override;
	EColor GetTurn() const override;
	EGameState GetState() const;
	PositionList GetMoves(Position piecePos) const override;
	std::string GetFenString() const override;
	
	// tie invitation
	void MakeTieRequest() override;
	bool IsTieRequest() const override;
	void TieRequestResponse(bool answer) override;

	// pawn evolve
	bool IsPawnEvolving() const override;
	void EvolvePawn(EType PieceType) override;

	// game over states
	bool IsCheck() const override;
	bool IsTie() const override;
	bool BlackWon() const override;
	bool WhiteWon() const override;
	bool IsGameOver() const override;

	void Restart() override;

	void AddListener(ListenerWeakPtr listener) override;
	void RemoveListener(IGameListener* listener) override;
	
	void Notify(Response response);
	void Notify(Position start, Position end);



private:
	Board m_board;
	EColor m_turn;
	EGameState m_state;
	BoardConfigList boardConfigs;
	std::vector<ListenerWeakPtr> m_listeners;
};


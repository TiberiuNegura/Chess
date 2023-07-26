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

using CharBoardRepresentation = std::array<std::array<char, 8>, 8>;
using BitVector = std::vector<std::bitset<256>>;

class Game : public IGame
{
public:
	// Constructor
	Game();
	Game(CharBoardRepresentation mat, EColor turn, EGameState state);

	void MovePiece(Position start, Position destination) override;
	//void MakeCastling(std::string where) override;
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
	void EvolvePawn(const std::string& pieceName) override;

	// game over states
	bool IsCheck() const override;
	bool IsTie() const override;
	bool BlackWon() const override;
	bool WhiteWon() const override;
	bool IsGameOver() const override;

	void RestartRequest(IGamePtr& newGame) override;
	void RestartGame(IGamePtr& newGame);

	void AddListener(IGameListener* listener) override;
	void RemoveListener(IGameListener* listener) override;
	
	void Notify(Response response);
	void Notify(Position start, Position end, const PositionList& possibleMoves);

private:
	Board m_board;
	EColor m_turn;
	EGameState m_state;
	BitVector boardConfigs;
	std::vector<IGameListener*> listeners;
};


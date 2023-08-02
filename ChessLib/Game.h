#pragma once

#include <set>

#include "IGame.h"
#include "Board.h"
#include "IGameListener.h"

using ListenerList = std::vector<ListenerWeakPtr>;

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
	Game(std::string& fileContent, LoadType fileType);


	void LoadFromFEN(std::string fen);
	void LoadFromPGN(std::string pgn);
	Move ChessMoveToMatrix(const std::string& move);


	void MovePiece(Position start, Position destination) override;
	void UpdateTurn();
	void UpdateState(EGameState state);

	// Getters
	MatrixPtr GetBoard() const override;
	EColor GetTurn() const override;
	EGameState GetState() const;
	PositionList GetMoves(Position piecePos) const override;
	TypeList GetWhiteMissingPieces() const override;
	TypeList GetBlackMissingPieces() const override;
	std::string GetFenString() const override;
	std::string GetPgnMove() const override;
	std::string GetPGN() const;
	
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
	bool FindSubstring(std::string input, const std::set<std::string>& substrings) const;

	void Restart() override;

	void AddListener(ListenerWeakPtr listener) override;
	void RemoveListener(IGameListener* listener) override;
	
	void Notify(Response response);
	void Notify(Position start, Position end);
	void Notify(EType pieceType, EColor pieceColor);



private:
	Board m_board;
	EColor m_turn;
	EGameState m_state;
	BoardConfigList boardConfigs;
	TypeList m_whiteMissing, m_blackMissing;
	MovesList m_moves;
	ListenerList m_listeners;
};


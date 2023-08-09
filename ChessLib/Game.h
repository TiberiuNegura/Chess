#pragma once

#include <set>

#include "IGame.h"
#include "Board.h"
#include "IGameListener.h"
#include "ITimerListener.h"
#include "Timer.h"

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

class Game : public IGame, public ITimerListener, public std::enable_shared_from_this<Game>, public IGameStatus
{
public:
	// Constructor
	Game();
	Game(CharBoardRepresentation mat, EColor turn, EGameState state);

	bool LoadFromFormat(const std::string& path) override;
	void LoadFromFEN(std::string fen);
	void LoadFromPGN(PGN pgnObj, bool loadFromBackup = false);
	Move ChessMoveToMatrix(const std::string& move);

	void PreviewPastConfig(int moveIndex) override;


	void MovePiece(Position start, Position destination) override;
	void UpdateTurn();
	void UpdateState(EGameState state);

	// Getters
	MatrixPtr GetBoard() const override;
	EColor GetTurn() const override;
	EGameState GetState() const;
	PositionList GetMoves(Position piecePos) const override;
	TypeList GetMissingPieces(EColor color) const override;
	MovesList GetMovesList() const override;

	std::string GetFenString() const;
	PGN GetPGN() const;
	void SavePGN(const std::string& path) const override;
	void SaveFEN(const std::string& path) const override;


	const IGameStatus* Status() const override;

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

	bool FindSubstring(std::string input, const std::set<std::string>& substrings) const;

	void PlayPauseTimer() override;
	void StopTimer() override;
	bool IsTimerPaused() const override;

	void AddListener(ListenerWeakPtr listener) override;
	void RemoveListener(IGameListener* listener) override;
	
	void Notify(Response response);
	void Notify(Position start, Position end);
	void Notify(EType pieceType, EColor pieceColor);
	void Notify(int whiteTimer, int blackTimer);

	void OnSecondPass() override;

private:
	Board m_board;
	EColor m_turn;
	EGameState m_state;
	BoardConfigList m_boardConfigs;
	TypeList m_whiteMissing, m_blackMissing;
	ListenerList m_listeners;
	PGN m_pgn;
	MovesList m_gameMoves;
	bool m_sendNotifications;
	Timer m_timer;
	int m_whiteTimer, m_blackTimer;

};


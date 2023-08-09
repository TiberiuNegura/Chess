#pragma once

#include <set>

#include "IGame.h"
#include "Board.h"
#include "ITimerListener.h"
#include "Timer.h"
#include "PGN.h"

enum class EGameState
{
	Playing,
	TieRequest,
	Tie,
	PawnEvolving,
	BlackWon,
	WhiteWon,
	Check,
	Pause
};

enum class EResponse
{
	Check,
	PawnUpgrade,
	TieRequest,
	WhiteWon,
	BlackWon,
	Tie,
	Restart
};

class Game : public IGame, public IGameStatus, public ITimerListener, public std::enable_shared_from_this<Game>
{
public:
	// Constructor
	Game();
	Game(CharBoardRepresentation mat, EColor turn, EGameState state);

	// IGame methods
	void AddListener(ListenerWeakPtr listener) override;
	void RemoveListener(IGameListener* listener) override;

	void MovePiece(Position start, Position destination) override;
	void MakeTieRequest() override;
	void TieRequestResponse(bool answer) override;
	void EvolvePawn(EType PieceType) override;

	void Pause() override;
	void Resume() override;
	void Stop() override;
	void Restart() override;

	const IGameStatus* Status() const override;

	void PlayPauseTimer() override;
	bool IsTimerPaused() const override;

	void SavePGN(const std::string& path) const override;
	void SaveFEN(const std::string& path) const override;
	bool LoadFromFormat(const std::string& path) override;

	void PreviewPastConfig(int moveIndex) override;

	// IGameStatus methods
	EColor GetTurn() const override;

	MatrixPtr GetBoard() const override;
	PositionList GetMoves(Position piecePos) const override;
	TypeList GetMissingPieces(EColor color) const override;
	MovesList GetMovesList() const override;

	bool IsPawnEvolving() const override;
	bool IsTieRequest() const override;
 
	bool IsCheck() const override;
	bool IsTie() const override;
	bool BlackWon() const override;
	bool WhiteWon() const override;
	bool IsGameOver() const override;

	// ITimerListener methods
	void OnSecondPass() override;


	// State changes
	EGameState GetState() const;
	void UpdateState(EGameState state);
	void UpdateTurn();

	// Game storage methods
	std::string GetFenString() const;
	PGN GetPGN() const;
	bool FindSubstring(std::string input, const std::set<std::string>& substrings) const;

	void LoadFromFEN(std::string fen);
	void LoadFromPGN(PGN pgnObj, bool loadFromBackup = false);
	Move ChessMoveToMatrix(const std::string& move);
	
	// Listeners notifications
	void Notify(EResponse response);
	void Notify(Position start, Position end);
	void Notify(EType pieceType, EColor pieceColor);
	void Notify(int whiteTimer, int blackTimer);


private:
	EGameState m_currentState, m_lastState;
	EColor m_turn;

	Board m_board;
	BoardConfigList m_boardConfigs;
	TypeList m_whiteMissing, m_blackMissing;
	MovesList m_gameMoves;

	bool m_bEnableNotifications;
	ListenerList m_listeners;

	Timer m_timer;
	int m_whiteTimer, m_blackTimer;

	PGN m_pgn;
};


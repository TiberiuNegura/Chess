#pragma once

#include "IGameStatus.h"
#include "IGameListener.h"

#include "Position.h"
#include "AllChessExceptions.h"

using IGamePtr = std::shared_ptr<class IGame>;

class IGame
{
public:
	static IGamePtr Produce(int timerSeconds = 0);

	virtual ~IGame() = default;

	// For observer
	virtual void AddListener(ListenerWeakPtr listener) = 0;
	virtual void RemoveListener(IGameListener* listener) = 0;

	// Game commands
	virtual void MovePiece(Position start, Position destination) = 0;
	virtual void MakeTieRequest() = 0;
	virtual void TieRequestResponse(bool answer) = 0;
	virtual void EvolvePawn(EType pieceType) = 0;

	// Game controls
	virtual void Start() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Stop() = 0; 
	virtual void Restart() = 0;

	virtual bool HadStarted() const = 0;
	virtual bool IsPaused() const = 0; 

	// Game status getters
	virtual const IGameStatus* Status() const = 0;

	// Timer
	// virtual ITimerInfo* TimerInfo() const = 0; // TODO to add

	// Game storage formats
	virtual void SavePGN(const std::string& path) const = 0;
	virtual void SaveFEN(const std::string& path) const = 0;
	virtual bool LoadFromFormat(const std::string& path) = 0;

	// Back visualization
	virtual void PreviewPastConfig(int moveIndex) = 0;
};



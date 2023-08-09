#pragma once

#include "IGameStatus.h"
#include "IPiece.h"
#include "IGameListener.h"
#include "PGN.h"

#include "AllChessExceptions.h"

using IGamePtr = std::shared_ptr<class IGame>;
using ListenerWeakPtr = std::weak_ptr<IGameListener>;

enum class LoadType
{
	PGN,
	FEN
};

class IGame
{
public:
	static IGamePtr Produce(); 

	virtual void MovePiece(Position start, Position destination) = 0;

	// Game storage formats
	virtual void SavePGN(const std::string& path) const = 0;
	virtual void SaveFEN(const std::string& path) const = 0;
	virtual bool LoadFromFormat(const std::string& path) = 0;

	virtual void PreviewPastConfig(int moveIndex) = 0;

	// Game events

	virtual void MakeTieRequest() = 0;
	virtual void TieRequestResponse(bool answer) = 0;
	virtual void EvolvePawn(EType pieceType) = 0;

	// Game status getters
	virtual const IGameStatus* Status() const = 0;

	// Timer
	virtual void PlayPauseTimer() = 0;
	virtual void StopTimer() = 0;
	virtual bool IsTimerPaused() const = 0;

	// For observer
	virtual void AddListener(ListenerWeakPtr listener) = 0;
	virtual void RemoveListener(IGameListener* listener) = 0;

	// Game restart
	virtual void Restart() = 0;

	~IGame() = default;
};




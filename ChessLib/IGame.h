#pragma once

#include "IGameStatus.h"
#include "IGameListener.h"
#include "IGameControls.h"
#include "IGameStorage.h"

#include "Position.h"
#include "AllChessExceptions.h"

using IGamePtr = std::shared_ptr<class IGame>;

class IGame : public IGameControls, public IGameStorage
{
public:
	static IGamePtr Produce(int timerSeconds = 600);

	virtual ~IGame() = default;

	// For observer
	virtual void AddListener(ListenerWeakPtr listener) = 0;
	virtual void RemoveListener(IGameListener* listener) = 0;

	// Game commands
	virtual void MovePiece(Position start, Position destination) = 0;
	virtual void MakeTieRequest() = 0;
	virtual void TieRequestResponse(bool answer) = 0;
	virtual void EvolvePawn(EType pieceType) = 0;

	// Game status getters
	virtual const IGameStatus* Status() const = 0;

	// Timer
	// virtual ITimerInfo* TimerInfo() const = 0; // TODO to add

	// Back visualization
	virtual void PreviewPastConfig(int moveIndex) = 0;
};



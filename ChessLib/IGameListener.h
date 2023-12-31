#pragma once

#include "IPiece.h"

#include <vector>
#include <memory>
#include <string>
#include <chrono>

using namespace std::chrono;

class IGameListener
{
public:
	virtual void OnGameOver() = 0;
	virtual void OnCheck(std::string msg) = 0;
	virtual void OnPawnEvolve() = 0;
	virtual void OnTieRequest() = 0;
	virtual void OnMovePiece(Position start, Position end, milliseconds elapsedTime) = 0;
	virtual void OnPieceCapture(EType pieceType, EColor pieceColor) = 0;
	virtual void OnRestart() = 0;
	virtual void OnTimerTick(milliseconds whiteTimer, milliseconds blackTimer) = 0;

	virtual ~IGameListener() = default;
};

using ListenerWeakPtr = std::weak_ptr<IGameListener>;
using ListenerList = std::vector<ListenerWeakPtr>;
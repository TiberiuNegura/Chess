#pragma once

#include "IPiece.h"
#include "CheckException.h"

#include <vector>
#include <memory>

class IGameListener
{
public:

	virtual void OnGameOver() = 0;
	virtual void OnCheck(std::string msg) = 0;
	virtual void OnPawnEvolve() = 0;
	virtual void OnTieRequest() = 0;
	virtual void OnMovePiece(Position start, Position end) = 0;
	virtual void OnPieceCapture(EType pieceType, EColor pieceColor) = 0;
	virtual void OnRestart() = 0;
	virtual void OnTimePass(int whiteTimer, int blackTimer) = 0;


	virtual ~IGameListener() = default;
};

using ListenerWeakPtr = std::weak_ptr<IGameListener>;
using ListenerList = std::vector<ListenerWeakPtr>;
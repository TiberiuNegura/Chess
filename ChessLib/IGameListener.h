#pragma once

#include "IPiece.h"
#include "CheckException.h"

class IGameListener
{
public:

	virtual void OnGameOver() = 0;
	virtual void OnCheck(std::string msg) = 0;
	virtual void OnPawnEvolve() = 0;
	virtual void OnTieRequest() = 0;
	virtual void OnMovePiece(Position start, Position end, const PositionList& possibleMoves) = 0;
	virtual void OnRestart() = 0;


	virtual ~IGameListener() = default;
};
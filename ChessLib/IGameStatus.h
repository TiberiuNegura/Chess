#pragma once

#include "IPiece.h"

class IGameStatus
{
public:
	~IGameStatus() = default;

	// Current turn
	virtual EColor GetTurn() const = 0;

	// tie invitation
	virtual bool IsTieRequest() const = 0;

	// pawn evolving
	virtual bool IsPawnEvolving() const = 0;

	// Game over states
	virtual bool IsCheck() const = 0;
	virtual bool IsTie() const = 0;
	virtual bool BlackWon() const = 0;
	virtual bool WhiteWon() const = 0;
	virtual bool IsGameOver() const = 0;

};

#pragma once

#include "IPiece.h"
#include "Position.h"

using Move = std::pair<Position, Position>;
using MovesList = std::vector<Move>;

class IMatrix
{
public:
	virtual IPiecePtr GetElement(Position element) = 0;

	virtual ~IMatrix() = default;
};

using MatrixPtr = std::shared_ptr<IMatrix>;

class IGameStatus
{
public:
	virtual ~IGameStatus() = default;

	virtual bool IsTimerEnabled() const = 0;
	virtual bool IsStarted() const = 0;
	virtual bool IsPaused() const = 0;

	virtual EColor GetTurn() const = 0;

	virtual MatrixPtr GetBoard() const = 0;
	virtual PositionList GetMoves(Position piecePos) const = 0;
	virtual TypeList GetMissingPieces(EColor color) const = 0;
	virtual MovesList GetMovesList() const = 0;

	virtual bool IsPawnEvolving() const = 0;
	virtual bool IsTieRequest() const = 0;

	// Game over states
	virtual bool IsCheck() const = 0;
	virtual bool IsTie() const = 0;
	virtual bool BlackWon() const = 0;
	virtual bool WhiteWon() const = 0;
	virtual bool IsGameOver() const = 0;


};

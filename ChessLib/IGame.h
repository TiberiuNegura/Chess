#pragma once

#include "IPiece.h"
#include "IGameListener.h"

#include "CheckException.h"
#include "ChessException.h"
#include "EmptyPositionException.h"
#include "GameOverException.h"
#include "IllegalMoveException.h"
#include "InvalidOptionException.h"
#include "OutOfBoundsException.h"
#include "PawnEvolveException.h"
#include "PieceNotFoundException.h"
#include "TieRequestException.h"

using IGamePtr = std::shared_ptr<class IGame>;
using ListenerWeakPtr = std::weak_ptr<IGameListener>;

class IMatrix
{
public:
	virtual IPiecePtr GetElement(Position element) = 0;	

	virtual ~IMatrix() = default;
};


using MatrixPtr = std::shared_ptr<IMatrix>;

class IGame
{
public:
	static IGamePtr Produce(); 
	static IGamePtr Produce(const std::string& FenString);

	virtual void MovePiece(Position start, Position destination) = 0;
	
	// Getters
	virtual MatrixPtr GetBoard() const = 0;
	virtual EColor GetTurn() const = 0;
	virtual PositionList GetMoves(Position piecePos) const = 0;
	virtual std::string GetFenString() const = 0;

	// tie invitation
	virtual void MakeTieRequest() = 0;
	virtual bool IsTieRequest() const = 0;
	virtual void TieRequestResponse(bool answer) = 0;

	// pawn evolving
	virtual bool IsPawnEvolving() const = 0;
	virtual void EvolvePawn(EType pieceType) = 0;

	// Game over states
	virtual bool IsCheck() const = 0;
	virtual bool IsTie() const = 0;
	virtual bool BlackWon() const = 0;
	virtual bool WhiteWon() const = 0;
	virtual bool IsGameOver() const = 0;

	virtual void Restart() = 0;

	// for observer
	virtual void AddListener(ListenerWeakPtr listener) = 0;
	virtual void RemoveListener(IGameListener* listener) = 0;

	~IGame() = default;
};


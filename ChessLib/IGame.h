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

class IMatrix
{
public:
	virtual IPiecePtr GetElement(Position element) = 0;	

	virtual ~IMatrix() = default;
};


using MatrixPtr = std::shared_ptr<IMatrix>;

enum class Response
{
	CHECK,
	PAWN_UPGRADE,
	TIE_REQUEST,
	WHITE_WON,
	BLACK_WON,
	TIE,
	RESTART
};

class IGame
{
public:
	static IGamePtr Produce(); 

	virtual void MovePiece(Position start, Position destination) = 0;
	//virtual void MakeCastling(std::string where) = 0;
	
	// Getters
	virtual MatrixPtr GetBoard() const = 0;
	virtual EColor GetTurn() const = 0;
	virtual PositionList GetMoves(Position piecePos) const = 0;

	// tie invitation
	virtual void MakeTieRequest() = 0;
	virtual bool IsTieRequest() const = 0;
	virtual void TieRequestResponse(bool answer) = 0;

	// pawn evolving
	virtual bool IsPawnEvolving() const = 0;
	virtual void EvolvePawn(const std::string& pieceName) = 0;

	// Game over states
	virtual bool IsCheck() const = 0;
	virtual bool IsTie() const = 0;
	virtual bool BlackWon() const = 0;
	virtual bool WhiteWon() const = 0;
	virtual bool IsGameOver() const = 0;

	virtual void RestartRequest(IGamePtr& newGame) = 0;

	// for observer
	virtual void AddListener(IGameListener* listener) = 0;
	virtual void RemoveListener(IGameListener* listener) = 0;
	/*virtual void Notify(Response response) = 0;
	virtual void Notify(Position start, Position end, const PositionList& possibleMoves) = 0;*/

	~IGame() = default;
};


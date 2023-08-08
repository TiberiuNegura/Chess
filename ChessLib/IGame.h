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

class IMatrix
{
public:
	virtual IPiecePtr GetElement(Position element) = 0;	

	virtual ~IMatrix() = default;
};


using MatrixPtr = std::shared_ptr<IMatrix>;
using Move = std::pair<Position, Position>;
using MovesList = std::vector<Move>;

class IGame
{
public:
	static IGamePtr Produce(); 


	virtual void MovePiece(Position start, Position destination) = 0;
	
	// Getters
	virtual MatrixPtr GetBoard() const = 0;
	virtual PositionList GetMoves(Position piecePos) const = 0;
	virtual TypeList GetMissingPieces(EColor color) const = 0;
	virtual MovesList GetMovesList() const = 0;

	// Game storage formats
	virtual void SavePGN(std::string path) const = 0;
	virtual void SaveFEN(std::string path) const = 0;
	virtual bool LoadFromFormat(std::string path) = 0;

	virtual void PreviewPastConfig(int moveIndex) = 0;


	virtual void MakeTieRequest() = 0;
	virtual void TieRequestResponse(bool answer) = 0;
	virtual void EvolvePawn(EType pieceType) = 0;
	virtual void Restart() = 0;

	// Game status operations
	virtual const IGameStatus* Status() const = 0;

	// Timer
	virtual void PlayPauseTimer() = 0;
	virtual void StopTimer() = 0;

	// for observer
	virtual void AddListener(ListenerWeakPtr listener) = 0;
	virtual void RemoveListener(IGameListener* listener) = 0;

	~IGame() = default;
};




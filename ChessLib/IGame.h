#pragma once

#include "IPiece.h"

using IGamePtr = std::shared_ptr<class IGame>;

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

	virtual bool IsCheck(EColor color) const = 0;
	virtual bool IsCheckmate(EColor color) const = 0;
	virtual void MovePiece(Position start, Position destination) = 0;
	
	virtual MatrixPtr GetBoard() const = 0;
	virtual PositionList GetMoves(Position piecePos) const = 0;
	virtual EColor GetTurn() const = 0;

	~IGame() = default;
};


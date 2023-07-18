#pragma once

#include "IPiece.h"

using IPiecePtr = std::shared_ptr<IPiece>;

class IMatrix
{
public:
	virtual IPiecePtr GetElement(Position element) = 0;
};


using MatrixPtr = std::shared_ptr<IMatrix>;

class IGame
{
public:
	virtual void StartGame() = 0;
	virtual bool IsCheck(Position king) = 0;
	virtual bool IsCheckmate() = 0;
	virtual void MovePiece(Position start, Position destination) = 0;
	virtual MatrixPtr GetBoard() = 0;

	~IGame() = default;
};


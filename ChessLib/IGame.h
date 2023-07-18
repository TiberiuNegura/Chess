#pragma once

#include "IPiece.h"

using IPiecePtr = std::shared_ptr<IPiece>;
using IGamePtr = std::shared_ptr<class IGame>;

class IMatrix
{
public:
	virtual IPiecePtr GetElement(Position element) = 0;	
};


using MatrixPtr = std::shared_ptr<IMatrix>;

class IGame
{
public:
	static IGamePtr StartGame(); // factory
	virtual bool IsCheck(Color color) = 0;
	virtual bool IsCheckmate(Color color) = 0;
	virtual void MovePiece(Position start, Position destination) = 0;
	virtual MatrixPtr GetBoard() = 0;
	virtual PositionList GetPattern(Position piecePos) = 0;
	virtual Color GetTurn() = 0;

	// TODO: player`s turn 

	~IGame() = default;
};


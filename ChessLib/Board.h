#pragma once

#include "IGame.h"
#include "Piece.h"

using Matrix = std::array<std::array<PiecePtr, 8>, 8>;
using BoardPtr = std::shared_ptr<class Board>;

class Board
{	
public:

	Board();
	Board(const Matrix& mat);

	// Inherited via BoardInterface
	const Matrix& GetMatrix() const;
	PiecePtr Get(int i, int j) const;
	PiecePtr Get(Position pos) const;
	PositionList GetMoves(Position piecePos, EColor turn) const;

	BoardPtr Clone() const;

	void MovePiece(Position start, Position end);
	void SetPosition(PiecePtr toRevert, Position pos);

	bool IsEmptyPosition(Position p) const;
	static bool IsOutOfBounds(Position p);
	bool IsCheck(EColor color) const;
	bool IsCheckmate(EColor color) const;

private:
	Position FindKing(EColor color) const;
	PositionList ComputePositionList(Position start, PiecePtr piece) const;

private:
	Matrix m_board;
};



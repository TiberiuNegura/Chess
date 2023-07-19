#pragma once

#include "IGame.h"
#include "Piece.h"

using Matrix = std::array<std::array<PiecePtr, 8>, 8>;

class Board
{
public:

	Board();
	Board(const Matrix& mat);

	// Inherited via BoardInterface
	const Matrix& GetGameBoard() const;

	bool IsEmpty(Position p) const;

	PiecePtr Get(int i, int j) const;
	PiecePtr Get(Position pos) const;

	PositionList ComputePositionList(Position start, std::vector<PositionList> positions) const;
	void MovePiece(Position start, Position end);
	void SetPosition(PiecePtr toRevert, Position pos);
	static bool IsOutOfBounds(Position p);

	bool IsCheck(EColor color) const;

	PositionList GetMoves(Position piecePos, EColor turn) const;

	Position FindKing(EColor color) const;

	std::shared_ptr<Board> Clone() const;

	PiecePtr operator[](Position pos) const;

private:
	Matrix m_board;
};


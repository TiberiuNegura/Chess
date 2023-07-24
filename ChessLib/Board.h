#pragma once

#include "IGame.h"
#include "Piece.h"

using Matrix = std::array<std::array<PiecePtr, 8>, 8>;
using BoardPtr = std::shared_ptr<class Board>;

class Board
{	
public:

	Board();
	Board(std::array<std::array<char, 8>, 8> alternateMat);
	Board(const Matrix& mat);

	EColor CharToColor(char c) const;
	EType CharToType(char c) const;
	// Inherited via BoardInterface
	const Matrix& GetMatrix() const;
	PiecePtr Get(int i, int j) const;
	PiecePtr Get(Position pos) const;
	void Set(Position pos, PiecePtr newPiece);
	PositionList GetMoves(Position piecePos, EColor turn) const;

	BoardPtr Clone() const;

	void MovePiece(Position start, Position end);
	/*void Castling(EColor color, std::string where);*/
	void SetPosition(PiecePtr toRevert, Position pos);

	bool IsCastlingPossible(std::string where, EColor color) const;
	bool IsEmptyPosition(Position p) const;
	static bool IsOutOfBounds(Position p);
	bool IsCheck(EColor color) const;
	bool IsCheckmate(EColor color) const;
	bool CanBeCaptured(Position pos, EColor color) const;
	bool CanPawnEvolve(Position pos) const;
	Position FindEvolvingPawn(EColor color);
	PositionList ComputePositionList(Position start, PiecePtr piece) const;

private:
	Position FindKing(EColor color) const;

private:
	Matrix m_board;
};



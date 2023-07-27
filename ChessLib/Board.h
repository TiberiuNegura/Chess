#pragma once

#include <bitset>


#include "IGame.h"
#include "Piece.h"

using BoardConfig = std::bitset<256>;
using BoardConfigList = std::vector<BoardConfig>;

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
	
	void Init();
	void Reset();

	BoardPtr Clone() const;

	void MovePiece(Position start, Position end);
	void SetPosition(PiecePtr toRevert, Position pos);

	bool IsCastlingPossible(std::string where, EColor color) const;
	bool IsEmptyPosition(Position p) const;
	static bool IsOutOfBounds(Position p);
	bool IsCheck(EColor color) const;
	bool IsCheckmate(EColor color) const;
	bool CanBeCaptured(Position pos, EColor color) const;
	bool CanPawnEvolve(Position pos) const;
	bool IsThreeFold(BoardConfigList threeFold, BoardConfig configuration) const;

	Position FindEvolvingPawn(EColor color);
	PositionList ComputePositionList(Position start, PiecePtr piece) const;
	BoardConfig GetBoardConfiguration() const;


private:
	Position FindKing(EColor color) const;

private:
	Matrix m_board;
};



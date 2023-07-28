#pragma once

#include <bitset>


#include "IGame.h"
#include "Piece.h"


using BoardConfig = std::bitset<256>;
using BoardConfigList = std::vector<BoardConfig>;

using CharBoardRepresentation = std::array<std::array<char, 8>, 8>;
using Matrix = std::array<std::array<PiecePtr, 8>, 8>;
using BoardPtr = std::shared_ptr<class Board>;

enum class ECastling
{
	Left,
	Right,
};

class Board
{	
public:

	Board();
	Board(CharBoardRepresentation alternateMat);
	Board(const Matrix& mat);
	Board(const std::string& fenString);

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

	bool IsCastlingPossible(ECastling option, EColor color) const;
	bool IsEmptyPosition(Position p) const;
	static bool IsOutOfBounds(Position p);
	bool IsCheck(EColor color) const;
	bool IsCheckmate(EColor color) const;
	bool CanBeCaptured(Position pos, EColor color) const;
	bool CanPawnEvolve(Position pos) const;
	bool IsThreeFold(BoardConfigList boardConfigs, BoardConfig config) const;

	Position FindEvolvingPawn(EColor color);
	PositionList ComputePositionList(Position start) const;
	BoardConfig GetBoardConfiguration() const;
	std::string GetFenString() const;
	TypeList SearchMissingPieces(EColor color) const;

	PiecePtr operator[](Position pos);

private:
	Position FindKing(EColor color) const;

private:
	Matrix m_board;
};


